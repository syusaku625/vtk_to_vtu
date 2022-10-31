#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<list>
#include <boost/algorithm/string.hpp>
#include<boost/progress.hpp>
#include<set>
#include<cmath>
#include <iomanip>
using namespace std;

void export_element_part(string filename, vector<vector<int>> element)
{
    ofstream ofs(filename);
    for(int i=0; i<element.size(); i++){
        for(int j=0; j<element[i].size(); j++){
            ofs << element[i][j] << " ";
        }
        ofs << endl;
    }
    ofs.close();
}

void export_element_id(string filename, vector<vector<int>> element)
{
    boost::progress_display show_progress(element.size());
    ofstream ofs(filename);
    for(int i=0; i<element.size(); i++){
        ++show_progress;
        if(element[i].size()==4) ofs << 10 << endl;
        if(element[i].size()==6) ofs << 13 << endl;
    }
    ofs.close();
}

void input_surface_node_and_element_construct(string filename, vector<vector<double>> &x, vector<vector<int>> &element)
{
    ifstream ifs(filename);
    string str;
    for(int i=0; i<5; i++){
        getline(ifs,str);
    }
    int numOfnode;
    istringstream ss(str);
    for(int i=0; i<3; i++){
        getline(ss, str, ' ');
        if(i==2) numOfnode=stoi(str);
    }
    cout << numOfnode << endl;
    for(int i=0; i<4; i++){
        getline(ifs,str);
    }
    int numOfelem;
    istringstream ss2(str);
    for(int i=0; i<3; i++){
        getline(ss2, str, ' ');
        if(i==2) numOfelem=stoi(str);
    }
    cout << numOfelem << endl;
    for(int i=0; i<2; i++){
        getline(ifs,str);
    }
    for(int i=0; i<numOfnode; i++){
        getline(ifs,str);
        istringstream ss1(str);
        vector<double> tmp_x;
        for(int j=0; j<3; j++){
            getline(ss1, str, ' ');
            tmp_x.emplace_back(stod(str));
        }
        x.emplace_back(tmp_x);
    }
    for(int i=0; i<numOfelem; i++){
        cout << i << endl;
        getline(ifs,str);
        istringstream ss3(str);
        vector<int> tmp_element;
        for(int j=0; j<4; j++){
            getline(ss3, str, ' ');
            cout << str << endl;
            if(j==0) continue;
            tmp_element.push_back(stoi(str));
        }
        element.push_back(tmp_element);
    }
}

void export_boundary_surface_node_and_element(string filename, string filename2, vector<vector<double>> x, vector<vector<double>> surface_x, vector<vector<int>> surface_elem)
{
    //cout << "check" << endl;
    boost::progress_display show_progress(x.size());
    ofstream ofs(filename);
    for(int i=0; i<x.size(); i++){
        ++show_progress;
        for(int j=0; j<surface_x.size(); j++){
            if(fabs(x[i][0]-surface_x[j][0])<0.0000001 && fabs(x[i][1]-surface_x[j][1])<0.0000001 && fabs(x[i][2]-surface_x[j][2])<0.0000001)
            {
                ofs << i << endl;
                break;
            }
        }
    }   
    ofs.close();

    cout << "output_surface_element" << endl;
    boost::progress_display show_progress2(surface_elem.size());
    ofs.open(filename2);
    for(int i=0; i<surface_elem.size(); i++){
        ++show_progress2;
        for(int j=0; j<surface_elem[i].size(); j++){
            for(int k=0; k<x.size(); k++){
                if(fabs(x[k][0]-surface_x[surface_elem[i][j]][0])<0.0000001 && fabs(x[k][1]-surface_x[surface_elem[i][j]][1])<0.0000001 && fabs(x[k][2]-surface_x[surface_elem[i][j]][2])<0.0000001)
                {
                    ofs << k << " ";
                    break;
                }
            }
        }
        ofs << endl;
    }
    ofs.close();
}

void export_element_connectivity(string filename, vector<vector<int>> element)
{
    ofstream ofs(filename);
    for(int i=0; i<element.size(); i++){
        for(int j=0; j<element[i].size(); j++){
            ofs << element[i][j] << " ";
        }
        ofs << endl;
    }
    ofs.close();
}

void export_node(string filename, vector<vector<double>> x)
{
    ofstream ofs(filename);
    for(int i=0; i<x.size(); i++){
        ofs << setprecision(8) << x[i][0] << " " << x[i][1] << " " << x[i][2] << endl;
    }
    ofs.close();
}

void file_read(string filename, vector<vector<double>> &x, vector<vector<int>> &element)
{
    string str;
    ifstream ifs(filename);
    for(int i=0; i<5; i++){
        getline(ifs,str);
    }
    istringstream iss(str);
    string s;
    int count = 0;
    int numOfNode;
    while (iss >> s) {
        if(count==1){
            numOfNode=stoi(s);
        }
        count++;
    }
    cout << numOfNode << endl;
    

    for(int i=0; i<numOfNode/3; i++){
        getline(ifs,str);
        istringstream node_str(str);
        vector<double> node_buf;
        while (getline(node_str, str, ' ')){
            try
            {
                node_buf.push_back(stod(str));
            }
            catch(const std::exception& e)
            {
                continue;
            }
        }
        for(int j=0; j<node_buf.size()/3; j++){
            vector<double> x_tmp;
            x_tmp.push_back(node_buf[j*3]);
            x_tmp.push_back(node_buf[j*3+1]);
            x_tmp.push_back(node_buf[j*3+2]);
            x.push_back(x_tmp);
        }
    }

    if(x.size()!=numOfNode){
        getline(ifs,str);
        istringstream node_str(str);
        vector<double> tmp_x;
        for(int i=0; i<3; i++){
            getline(node_str, str, ' ');
            tmp_x.push_back(stod(str));
        }
        x.push_back(tmp_x);
    }

    while(getline(ifs,str)){
        list<string> list_string;
        boost::split(list_string, str, boost::is_any_of(" "));
        if(*(list_string.begin())=="CONNECTIVITY") break;
    }
    list<int> cell_node;
    
    while(getline(ifs,str)){
        bool flag = false;
        vector<std::string> result;
        istringstream stream(str);
        string tmp_cell_id;
        while (getline(stream, tmp_cell_id, ' ')){
            count = 0;
            if(count==0){
                if(tmp_cell_id == "CELL_TYPES"){
                    flag = true;
                    break;
                } 
            }
            count++;
            try
            {
                cell_node.push_back(stoi(tmp_cell_id));

            }
            catch(const std::exception& e)
            {
                continue;
            }
        }
        if(flag) break;
    }
    istringstream cell_num_read(str);
    int numOfCell;
    string tmp_cell_type;
    count = 0;
    while (getline(cell_num_read, tmp_cell_type, ' ')){
        if(count==1){
            numOfCell = stoi(tmp_cell_type);
        } 
        count++;
    }
    vector<int> cell_type;
    for(int i=0; i<numOfCell; i++){
        getline(ifs,str);
        cell_type.push_back(stoi(str));
    }
    
    for(int i=0; i<cell_type.size(); i++){
        vector<int> tmp_element;
        int cell_construct_number;
        if(cell_type[i]==10) cell_construct_number = 4;
        else if(cell_type[i]==13) cell_construct_number = 6;
        for(int j=0; j<cell_construct_number; j++){
            try
            {
                tmp_element.push_back(*(cell_node.begin()));
                cell_node.pop_front();
            }
            catch(const std::exception& e)
            {
                continue;
            }
            
        }
        element.push_back(tmp_element);
    }
    ifs.close();
}

void export_vtu(const std::string &file, vector<vector<double>> node, vector<vector<int>> element)
{
    FILE *fp;
  if ((fp = fopen(file.c_str(), "w")) == NULL)
  {
    cout << file << " open error" << endl;
    exit(1);
  }

  fprintf(fp, "<VTKFile type=\"UnstructuredGrid\" version=\"1.0\" byte_order=\"LittleEndian\" header_type=\"UInt32\">\n");
  fprintf(fp, "<UnstructuredGrid>\n");
  fprintf(fp, "<Piece NumberOfPoints= \"%d\" NumberOfCells= \"%d\" >\n", node.size(), element.size());
  fprintf(fp, "<Points>\n");
  int offset = 0;
  fprintf(fp, "<DataArray type=\"Float64\" Name=\"Position\" NumberOfComponents=\"3\" format=\"appended\" offset=\"%d\"/>\n",offset);
  offset += sizeof(int) + sizeof(double) * node.size() * 3;
  fprintf(fp, "</Points>\n");

  fprintf(fp, "<Cells>\n");
  fprintf(fp, "<DataArray type=\"Int64\" Name=\"connectivity\" format=\"ascii\">\n");
  for (int i = 0; i < element.size(); i++){
    for (int j = 0; j < element[i].size(); j++) fprintf(fp, "%d ", element[i][j]);
    fprintf(fp, "\n");
  }
  fprintf(fp, "</DataArray>\n");
  fprintf(fp, "<DataArray type=\"Int64\" Name=\"offsets\" format=\"ascii\">\n");
  int num = 0;
  for (int i = 0; i < element.size(); i++)
  {
    num += element[i].size();
    fprintf(fp, "%d\n", num);
  }
  fprintf(fp, "</DataArray>\n");
  fprintf(fp, "<DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">\n");
  for (int i = 0; i < element.size(); i++) fprintf(fp, "%d\n", 10);
    
  fprintf(fp, "</DataArray>\n");
  fprintf(fp, "</Cells>\n");

  fprintf(fp, "<PointData>\n");
  fprintf(fp, "</PointData>\n");

  fprintf(fp, "<CellData>\n");
  fprintf(fp, "</CellData>\n");
  fprintf(fp, "</Piece>\n");
  fprintf(fp, "</UnstructuredGrid>\n");
  fprintf(fp, "<AppendedData encoding=\"raw\">\n");
  fprintf(fp, "_");
  fclose(fp);

  fstream ofs;
  ofs.open(file.c_str(), ios::out | ios::app | ios_base::binary);
  double *data_d = new double[node.size()*3];
  num = 0;
  int size=0;
  for (int ic = 0; ic < node.size(); ic++){
    data_d[num] = node[ic][0];
    num++;
    data_d[num] = node[ic][1];
    num++;
    data_d[num] = node[ic][2];
    num++;
  }
  size=sizeof(double)*node.size()*3;
  ofs.write((char *)&size, sizeof(size));
  ofs.write((char *)data_d, size);

  delete data_d;

  ofs.close();

  if ((fp = fopen(file.c_str(), "a")) == NULL)
  {
    cout << file << " open error" << endl;
    exit(1);
  }
  fprintf(fp, "\n</AppendedData>\n");
  fprintf(fp, "</VTKFile>\n");
  fclose(fp);
}


int main(int argc, char *argv[])
{
    if(argc!=2){
        cout << "error" << endl;
        cout << "please input vtk file" << endl;
        exit(1);
    }
    string file = argv[1];
    string filename = file + ".vtk";
    vector<vector<double>> x;
    vector<vector<int>> element;
    file_read(filename,x,element);
    //export_node_coordinate
    string node_file = file+"_node.dat";
    export_node(node_file,x);
    //export_element_connectivity
    string element_file = file+"_element.dat";
    export_element_connectivity(element_file, element);
    //export_meshtype
    export_element_id("elementMeshType.dat",element);
    cout << "surface_process" << endl;
    vector<vector<double>> surface_x;
    vector<vector<int>> surface_element;
    input_surface_node_and_element_construct("sc_frame.ply", surface_x, surface_element);
    export_boundary_surface_node_and_element("dirichlet_sc.dat", "innerSurface_sc.dat", x, surface_x, surface_element);

    export_vtu("test.vtu",x,element);
}