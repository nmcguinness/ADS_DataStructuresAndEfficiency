/// Demos the efficiency issues related to passing objects into data structures
#include <iostream>
#include "Book.h"
#include <list>
#include <vector>

//function declarations
void demoOperatorAndCopyConstructor();
void demoEmplace();
void demoEmplaceBack();
void demoInefficiencyOfCopiesAndDataStructures();
void demoEfficiencyOfPointersAndDataStructures();
void exerciseEmplace();

int main()
{
    cout << endl << "********************demoOperatorAndCopyConstructor********************" << endl;
    demoOperatorAndCopyConstructor();

    cout << endl << "********************demoInefficiencyOfCopiesAndDataStructures********************" << endl;
    demoInefficiencyOfCopiesAndDataStructures();

    cout << endl << "********************demoEfficiencyOfPointersAndDataStructures********************" << endl;
    demoEfficiencyOfPointersAndDataStructures();

    cout << endl << "********************demoEmplaceBack********************" << endl;
    demoEmplaceBack();

    cout << endl << "********************demoEmplace********************" << endl;
    demoEmplace();

    cout << endl << "********************exerciseEmplace********************" << endl;
    exerciseEmplace();
}

/// @brief Demos what methods (e.g. constructor, destructor, copy constructor) are called when we instanciate a book, and use assignment and copy constructors
void demoOperatorAndCopyConstructor() {
    Book a("AAAA", 100);
    cout << endl << a << endl;

    //assignment operator
    Book b = a;
    cout << endl << b << endl;

    //copy constructor
    Book c(a);
    cout << endl << c << endl;
}

/// @brief Demos that an initial constructor will be called and THEN a copy constructor will be called each time we add a book 
void demoInefficiencyOfCopiesAndDataStructures()
{
    cout << endl << "Constructing objects..." << endl;
    Book a("AAAA", 100);
    Book b("BBBB", 68);
    Book c("CCCC", 240);

    cout << endl << endl << "Adding objects using pass-by-value into the list..." << endl;
    list<Book> bookList;
    bookList.push_back(a);
    bookList.push_back(b);
    bookList.push_back(c);
}

/// @brief Demos that an initial constructor will be called and THEN a reference to the object will be passed each time we add a book 
void demoEfficiencyOfPointersAndDataStructures()
{
    cout << endl << "Constructing objects..." << endl;
    Book a("AAAA", 100);
    Book b("BBBB", 68);
    Book c("CCCC", 240);

    cout << endl << "Adding objects using pass-by-reference into the list..." << endl;
    list<Book*> bookList;
    bookList.push_back(&a);
    bookList.push_back(&b);
    bookList.push_back(&c);
}

/// @brief Demos use of emplace_back() to insert at the end of the list
/// 
/// Q. Why are emplace_front, emplace_back, emplace so much more efficient that push_back, push_front etc?
/// A. It's because the emplace methods construct the object IN-PLACE in the data structure unlike,
/// for example, push_back() which creates a temp object outside the structure and copies that object
/// into the structure using the copy constructor for the object.
/// e.g.
/// 
/// using emplace to add we call - constructor
/// using push_back to add we call - constructor, copy constructor
void demoEmplaceBack()
{
    list<Book> bookList;

    //better to use emplace and construct the object INSIDE the list, vector, or whatever data structure we are using
    bookList.emplace_back("GGGG", 250);
    bookList.emplace_back("HHHH", 550);
    bookList.emplace_back("IIII", 850);

    cout << endl << "Finished adding the books..." << endl;

    cout << endl << "Notice that when we use the for(in) type loop that we call the copy constructor..." << endl;

    //notice how when we use this form of the for() it calls Copy Constructor and Destructor - inefficient
    for (Book b : bookList) {
        cout << endl << b << endl;
    }
}

/// @brief Demos use of emplace() to insert at a specific position using an iterator with std::advance()
void demoEmplace()
{
    list<Book> bookList;

    bookList.emplace_back("AAAA", 250);
    bookList.emplace_back("BBBB", 550);
    bookList.emplace_back("DDDD", 850);

    auto it = bookList.begin();
    std::advance(it, 2);

    //how to use emplace to insert at a specific location
    bookList.emplace(it, "CCCC", 750);


    //notice how when we use this form of the for() it calls Copy Constructor and Destructor - inefficient
    for (Book b : bookList) {
        cout << endl << b << endl;
    }
}

void exerciseEmplace() {
    //vector of strings - start with "a", "d", "g", "s"
    vector<string> sVec = { "a","d", "g","s" };

    //print contents
    for (string s : sVec)
        cout << endl << s << endl;

    cout << endl << endl;
    //add "f" at the correct position using emplace()
    vector<string>::iterator it = sVec.begin();
    advance(it, 2);
    sVec.emplace(it, "f");
    //print contents
    for (string s : sVec)
        cout << endl << s << endl;

    cout << endl << endl;
    //add "b" at the correct position using emplace()
    vector<string>::iterator it1 = sVec.begin();
    advance(it1, 1);
    sVec.emplace(it1, "b");
    //print contents
    for (string s : sVec)
        cout << endl << s << endl;

    //add "z" at the correct position using emplace()
    sVec.emplace_back("z");

    //print contents
    for (string s : sVec)
        cout << endl << s << endl;
}

