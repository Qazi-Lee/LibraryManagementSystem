#include "pch.h"
#include "DataBase.h"


DataBase::DataBase(const std::string& str)
{
    init = str;
    m_con = new connection(init);
}

DataBase::~DataBase()
{
    m_con->disconnect();
    delete m_con;
    m_con = nullptr;
}

result DataBase::Select(const std::string& sql)
{
    try
    {
        // connect to the database.  in practice we may have to pass some
        // arguments to say where the database server is, and so on.
        // the constructor parses options exactly like libpq's
        // pqconnectdb/pqconnect, see:
        // https://www.postgresql.org/docs/10/static/libpq-connect.html


        // start a transaction.  in libpqxx, you always work in one.
        pqxx::work w(*m_con);

        // work::exec1() executes a query returning a single row of data.
        // we'll just ask the database to return the number 1 to us.
        //pqxx::result r = w.exec("SELECT password FROM \"Account\" WHERE \"Account\".account = '张三'");
        pqxx::result r = w.exec(sql);
        // commit your transaction.  if an exception occurred before this
        // point, execution will have left the block, and the transaction will
        // have been destroyed along the way.  in that case, the failed
        // transaction would implicitly abort instead of getting to this point.
        w.commit();

        // look at the first and only field in the row, parse it as an integer,
        // and print it.
        for (int i = 0; i < r.size(); i++) {
            for (int j = 0; j < r.front().size(); j++) {
                std::cout << r[i][j].name() << ":" << r[i][j].c_str() << " ";
            }
            std::cout << std::endl;
        }
        return r;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return result();
    }

}

int DataBase::Insert(const std::string& sql)
{
    try
    {
        pqxx::work w(*m_con);
        w.exec(sql);
        w.commit();
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 0;
    }
}

int DataBase::Update(const std::string& sql)
{
    try
    {
        pqxx::work w(*m_con);
        w.exec(sql);
        w.commit();
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 0;
    }
}

int DataBase::Delete(const std::string& sql)
{
    try
    {
        pqxx::work w(*m_con);
        w.exec(sql);
        w.commit();
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 0;
    }
}


