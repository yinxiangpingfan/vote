#include "student_database.h"
#include <vector>

auto OpenDB(std::string className)
{
    using namespace sqlite_orm;

    auto Db = make_storage(className + ".db",
        make_table("students",
            make_column("id", &Student::id, primary_key().autoincrement()),
            make_column("name", &Student::name),
            make_column("sex",&Student::sex)));
    Db.sync_schema();
    return Db;
}

std::vector<Student> GetAllStudents(std::string className)
{
    auto DB = OpenDB(className);
    return DB.get_all<Student>();
}