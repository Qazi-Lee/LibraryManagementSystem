#include<iostream>
#include<pqxx/pqxx>
using namespace pqxx;
class DataBase
{
public:
    DataBase(const std::string& str="dbname = postgres user = postgres password = lq040216 \ hostaddr = 127.0.0.1 port = 5432");
    ~DataBase();
    void ChooseTable(const std::string& str) { m_table = str; }
    result Select(const std::string& sql);
    int Insert(const std::string& sql);
    int Update(const std::string& sql);
    int Delete(const std::string& sql);
public:
    connection* m_con=nullptr;
    std::string init;
    std::string m_table;//操作指定表
};
