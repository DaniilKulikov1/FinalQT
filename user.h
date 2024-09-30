#ifndef USER_H
#define USER_H
#include <QString>

class User
{
private:
    QString name_p;
    QString password_p;

public:

    User();


    User(const QString& name, const QString& password) :name_p(name), password_p(password)
        {};


    QString& getName();
    QString& getPassword();


    void setName(const QString& name)
    {
        name_p = name;
    }

};
#endif // USER_H
