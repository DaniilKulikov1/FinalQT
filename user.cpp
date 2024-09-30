#include "user.h"

User::User()//
{
    name_p = " ";
    password_p = " ";
};


QString& User::getName()
{
    return name_p;
};

QString& User::getPassword()
{
    return password_p;
};


