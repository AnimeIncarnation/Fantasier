#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Mesh.hpp"




 //obj_loader
Mesh::Mesh(const std::string filename) 
{
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail())
    {
        std::cout << "Failed to open .obj file ¡°"<< filename <<"¡± at" << __FILE__ << " line: " << __LINE__ << std::endl;
        return;
    }
    std::string line;
    while (!in.eof()) 
    {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec4f v; v[3] = 1.f;
            for (int i = 0;i < 3;i++) iss >> v[i];
            verts.push_back(v);
        }
        else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            Vec4f n; n[3] = 1.f;
            for (int i = 0;i < 3;i++) iss >> n[i];
            norms.push_back(n.normalize());
        }
        else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            Vec2f uv;
            for (int i = 0;i < 2;i++) iss >> uv[i];
            texcoords.push_back({ uv.x, 1 - uv.y });
        }
        else if (!line.compare(0, 2, "f ")) {
            std::vector<int> f, t, n;
            int fid, tid, nid;
            iss >> trash;
            int cnt = 0;
            while (iss >> fid >> trash >> tid >> trash >> nid) {
                f.push_back(fid-1);
                t.push_back(tid-1);
                n.push_back(nid-1);
                cnt++;
            }
            vertInds.push_back(f);
            texcoordInds.push_back(t);
            normInds.push_back(n);
            if (3 != cnt) {
                std::cerr << "Error: the obj file is supposed to be triangulated" << std::endl;
                in.close();
                return;
            }
        }
    }
    in.close();
    std::cerr << "# v# " << VertexNum() << " f# " << IndiceNum() << " vt# " << texcoords.size() << " vn# " << norms.size() << std::endl;

}


void Mesh::SetMesh(std::string filename)
{
    Clear();
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof())
    {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec4f v; v[3] = 1.f;
            for (int i = 0;i < 3;i++) iss >> v[i];
            verts.push_back(v);
        }
        else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            Vec4f n; n[3] = 1.f;
            for (int i = 0;i < 3;i++) iss >> n[i];
            norms.push_back(n.normalize());
        }
        else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            Vec2f uv;
            for (int i = 0;i < 2;i++) iss >> uv[i];
            texcoords.push_back({ uv.x, 1 - uv.y });
        }
        else if (!line.compare(0, 2, "f ")) {
            std::vector<int> f, t, n;
            int fid, tid, nid;
            iss >> trash;
            int cnt = 0;
            while (iss >> fid >> trash >> tid >> trash >> nid) {
                f.push_back(fid - 1);
                t.push_back(tid - 1);
                n.push_back(nid - 1);
                cnt++;
            }
            vertInds.push_back(f);
            texcoordInds.push_back(t);
            normInds.push_back(n);
            if (3 != cnt) {
                std::cerr << "Error: the obj file is supposed to be triangulated" << std::endl;
                in.close();
                return;
            }
        }
    }
    in.close();
    std::cerr << "# v# " << VertexNum() << " f# " << IndiceNum() << " vt# " << texcoords.size() << " vn# " << norms.size() << std::endl;
}


int Mesh::VertexNum() {
    return (int)verts.size();
}

int Mesh::IndiceNum() {
    return (int)vertInds.size();
}

std::vector<int> Mesh::GetVInds(int idx) const 
{
    return vertInds[idx];
}

std::vector<int> Mesh::GetNInds(int idx) const
{
    return normInds[idx];
}

std::vector<int> Mesh::GetTInds(int idx) const
{
    return texcoordInds[idx];
}

Vec4f& Mesh::GetVerts(int i) {
    return verts[i];
}

Vec4f& Mesh::GetNorms(int i)
{
    return norms[i];
}

Vec2f& Mesh::GetTexcoords(int i)
{
    return texcoords[i];
}

void Mesh::Clear()
{
        std::vector<Vec4f> v1,v2;
        std::vector<Vec2f> v3;
        std::vector<std::vector<int>> i1,i2,i3;
        verts.swap(v1);
        norms.swap(v2);
        texcoords.swap(v3);
        vertInds.swap(i1);
        normInds.swap(i2);
        texcoordInds.swap(i3);

}
