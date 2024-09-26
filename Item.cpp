#include "Item.h"

Item:: Item(){ // base constructor sets empty attributes 
    this -> title = "";
    this -> author = "";
}

Item:: Item(std:: string title, std:: string author){
    this -> title = title;
    this -> author = author;
}

std:: string Item:: getTitle(){return this -> title;}

std:: string Item:: getAuthor(){return this -> author;}

void Item:: setTitle(std:: string title){
    this -> title = title;
}

void Item:: setAuthor(std:: string author){
    this -> author = author;
}

Item:: ~Item() {} 