#include "doctest.h"
#include "Notebook.hpp"
using namespace ariel;

using namespace std;


TEST_CASE("basic input") {
    ariel::Notebook notebook;
    notebook.write(/*page=*/100, /*row=*/100, /*column=*/50, Direction::Horizontal, "abcd");
    CHECK(notebook.read(/*page=*/100, /*row=*/99, /*column=*/51, Direction::Vertical, /*length=*/3)=="_b_");
    notebook.erase(/*page=*/100, /*row=*/99, /*column=*/51, Direction::Vertical, /*length=*/3);
    CHECK(notebook.read(/*page=*/100, /*row=*/100, /*column=*/49, Direction::Horizontal, /*length=*/5)=="_a~cd");
}
TEST_CASE("Edge cases") {
    for (int page = 222; page < 224; page++) {//running over 2 pages
        for (int row = 151; row < 153; ++row) {//running over 2 rows
            for (int column = 0; column < 100; column+=2) {//running over all the columns
                //running over all the possible lengths of string to this column
                for (int length = 0; length < 101-column ;length+=2) {
                    ariel::Notebook notebookTemp;
                    string str(static_cast<unsigned long>(length), 'a');//creates a string in size of the length
                            CHECK_NOTHROW(notebookTemp.write(/*page=*/page, /*row=*/row, /*column=*/column, Direction::Horizontal,str));
                            CHECK(notebookTemp.read(/*page=*/page, /*row=*/row, /*column=*/column, Direction::Horizontal,str.length())==str);
                            CHECK_NOTHROW(notebookTemp.erase(/*page=*/page, /*row=*/row, /*column=*/column, Direction::Horizontal,str.length()));
                }
            }
        }
    }
    ariel::Notebook notebook;
    //    make sure that it doesn't throw exception if we try to erase in empty place Vertical\Horizontal
            CHECK_NOTHROW(notebook.erase(/*page=*/99, /*row=*/99, /*column=*/51, Direction::Vertical, /*length=*/3));
            CHECK_NOTHROW(notebook.erase(/*page=*/99, /*row=*/99, /*column=*/51, Direction::Horizontal, /*length=*/3));
    //    make sure that it doesn't throw exception if we try to erase after erasing at the same place Vertical\Horizontal
            CHECK_NOTHROW(notebook.erase(/*page=*/99, /*row=*/99, /*column=*/41, Direction::Vertical,13));
            CHECK_NOTHROW(notebook.erase(/*page=*/99, /*row=*/99, /*column=*/41, Direction::Horizontal,13));

    //    make sure all the functions doesn't throw exception if the string\length bigger than 100 while direction Vertical
            CHECK_NOTHROW(notebook.write(/*page=*/100, /*row=*/99, /*column=*/0, Direction::Vertical, "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvw"));
            CHECK_NOTHROW(notebook.read(/*page=*/100, /*row=*/99, /*column=*/0, Direction::Vertical, 101));
            CHECK_NOTHROW(notebook.erase(/*page=*/100, /*row=*/99, /*column=*/0, Direction::Vertical,101));

    //    make sure all the functions doesn't throw exception if the string\length equal to 100 while direction Horizontal
            CHECK_NOTHROW(notebook.write(/*page=*/100, /*row=*/97, /*column=*/0, Direction::Horizontal, "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuv"));
            CHECK_NOTHROW(notebook.read(/*page=*/100, /*row=*/99, /*column=*/0, Direction::Horizontal, 100));
            CHECK_NOTHROW(notebook.erase(/*page=*/100, /*row=*/99, /*column=*/0, Direction::Horizontal,100));

    //    make sure all the functions doesn't throw exception if the string\length+column equal to 100 while direction Horizontal
            CHECK_NOTHROW(notebook.write(/*page=*/100, /*row=*/98, /*column=*/2, Direction::Horizontal, "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrst"));
            CHECK_NOTHROW(notebook.read(/*page=*/100, /*row=*/99, /*column=*/51, Direction::Horizontal, 49));
            CHECK_NOTHROW(notebook.erase(/*page=*/100, /*row=*/99, /*column=*/40, Direction::Horizontal,60));

//    reading from empty place, so it will show only ____
            CHECK(notebook.read(/*page=*/88, /*row=*/99, /*column=*/40, Direction::Horizontal,5)=="_____");
            CHECK(notebook.read(/*page=*/88, /*row=*/99, /*column=*/40, Direction::Vertical,5)=="_____");

    //    make sure all the functions doesn't throw exception if the string\length equal to 0 while direction Horizontal
            CHECK_NOTHROW(notebook.write(/*page=*/88, /*row=*/99, /*column=*/40, Direction::Horizontal,""));
            CHECK(notebook.read(/*page=*/88, /*row=*/99, /*column=*/40, Direction::Horizontal,0)=="");
            CHECK_NOTHROW(notebook.erase(/*page=*/88, /*row=*/99, /*column=*/40, Direction::Horizontal,0));

    //    make sure all the functions doesn't throw exception if the string\length equal to 0 while direction Vertical
            CHECK_NOTHROW(notebook.write(/*page=*/88, /*row=*/99, /*column=*/40, Direction::Vertical,""));
            CHECK(notebook.read(/*page=*/88, /*row=*/99, /*column=*/40, Direction::Vertical,0)=="");
            CHECK_NOTHROW(notebook.erase(/*page=*/88, /*row=*/99, /*column=*/40, Direction::Vertical,0));
}
TEST_CASE("exceptions check") {
    ariel::Notebook notebook;
    for (int i = 0; i <32 ; i++)
    {
        string s;
        s+= char(i);
        CHECK_THROWS(notebook.write(/*page=*/10, /*row=*/99, /*column=*/41, Direction::Vertical,s));
    }
        for (int i = 127; i <256 ; i++)
    {
        string s;
        s+= char(i);
        CHECK_THROWS(notebook.write(/*page=*/10, /*row=*/99, /*column=*/41, Direction::Vertical,s));
    }
    
//    make sure all the functions throws exception if the one of those parameters
//    page\row\column\string\length is negative while direction Horizontal\Vertical
    CHECK_THROWS(notebook.write(/*page=*/-1, /*row=*/99, /*column=*/41, Direction::Vertical,"~"));
    CHECK_THROWS(notebook.write(/*page=*/88, /*row=*/-4, /*column=*/41, Direction::Vertical,"~"));
    CHECK_THROWS(notebook.write(/*page=*/88, /*row=*/99, /*column=*/-8, Direction::Vertical,"~"));
    CHECK_THROWS(notebook.write(/*page=*/-12, /*row=*/99, /*column=*/41, Direction::Horizontal,"~"));
    CHECK_THROWS(notebook.write(/*page=*/88, /*row=*/-56, /*column=*/41, Direction::Horizontal,"~"));
    CHECK_THROWS(notebook.write(/*page=*/88, /*row=*/99, /*column=*/-9, Direction::Horizontal,"~"));

    CHECK_THROWS(notebook.read(/*page=*/-43, /*row=*/99, /*column=*/0, Direction::Horizontal, 101));
    CHECK_THROWS(notebook.read(/*page=*/100, /*row=*/-34, /*column=*/0, Direction::Horizontal, 101));
    CHECK_THROWS(notebook.read(/*page=*/100, /*row=*/99, /*column=*/-56, Direction::Horizontal, 101));
    CHECK_THROWS(notebook.read(/*page=*/100, /*row=*/99, /*column=*/0, Direction::Horizontal, -1));
    CHECK_THROWS(notebook.read(/*page=*/-21, /*row=*/99, /*column=*/0, Direction::Vertical, 101));
    CHECK_THROWS(notebook.read(/*page=*/100, /*row=*/-32, /*column=*/0, Direction::Vertical, 101));
    CHECK_THROWS(notebook.read(/*page=*/100, /*row=*/99, /*column=*/-56, Direction::Vertical, 101));
    CHECK_THROWS(notebook.read(/*page=*/100, /*row=*/99, /*column=*/0, Direction::Vertical, -6));

    CHECK_THROWS(notebook.erase(/*page=*/-54, /*row=*/99, /*column=*/0, Direction::Horizontal,101));
    CHECK_THROWS(notebook.erase(/*page=*/100, /*row=*/-31, /*column=*/0, Direction::Horizontal,101));
    CHECK_THROWS(notebook.erase(/*page=*/100, /*row=*/99, /*column=*/16, Direction::Horizontal,101));
    CHECK_THROWS(notebook.erase(/*page=*/100, /*row=*/99, /*column=*/0, Direction::Horizontal,-8));
    CHECK_THROWS(notebook.erase(/*page=*/-42, /*row=*/99, /*column=*/0, Direction::Vertical,101));
    CHECK_THROWS(notebook.erase(/*page=*/100, /*row=*/-45, /*column=*/0, Direction::Vertical,101));
    CHECK_THROWS(notebook.erase(/*page=*/100, /*row=*/99, /*column=*/-56, Direction::Vertical,101));
    CHECK_THROWS(notebook.erase(/*page=*/100, /*row=*/99, /*column=*/0, Direction::Vertical,-7));

//    writing the char ~ that is equal to erase Vertical\Horizontal
    CHECK_THROWS(notebook.write(/*page=*/88, /*row=*/99, /*column=*/40, Direction::Vertical,"~"));
    CHECK_THROWS(notebook.write(/*page=*/88, /*row=*/99, /*column=*/41, Direction::Horizontal,"~"));

//    make sure all the functions throws exception if the string\length bigger than 100 while direction Horizontal
    CHECK_THROWS(notebook.write(/*page=*/100, /*row=*/99, /*column=*/0, Direction::Horizontal, "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvw"));
    CHECK_THROWS(notebook.read(/*page=*/100, /*row=*/99, /*column=*/0, Direction::Horizontal, 101));
    CHECK_THROWS(notebook.erase(/*page=*/100, /*row=*/99, /*column=*/0, Direction::Horizontal,101));

//    make sure all the functions throws exception if the string\length+column bigger than 100 while direction Horizontal(so it will need to get to the next row)
    CHECK_THROWS(notebook.write(/*page=*/100, /*row=*/99, /*column=*/3, Direction::Horizontal, "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrst"));
    CHECK_THROWS(notebook.read(/*page=*/100, /*row=*/99, /*column=*/52, Direction::Horizontal, 49));
    CHECK_THROWS(notebook.erase(/*page=*/100, /*row=*/99, /*column=*/41, Direction::Horizontal,60));

    //    make sure that throws exception if we try to write after erasing at the same place Vertical\Horizontal
    notebook.erase(/*page=*/99, /*row=*/99, /*column=*/51, Direction::Vertical, /*length=*/3);
    CHECK_THROWS(notebook.write(/*page=*/99, /*row=*/101, /*column=*/51, Direction::Vertical, "abc"));
    notebook.erase(/*page=*/99, /*row=*/99, /*column=*/51, Direction::Horizontal, /*length=*/3);
    CHECK_THROWS(notebook.write(/*page=*/99, /*row=*/99, /*column=*/53, Direction::Horizontal, "abc"));

    //    make sure that throws exception if we try to write after writing at the same place Vertical\Horizontal
    notebook.write(/*page=*/101, /*row=*/101, /*column=*/51, Direction::Horizontal, "abc");
    CHECK_THROWS(notebook.write(/*page=*/101, /*row=*/101, /*column=*/53, Direction::Horizontal, "abc"));
    notebook.write(/*page=*/100, /*row=*/101, /*column=*/51, Direction::Vertical, "abc");
    CHECK_THROWS(notebook.write(/*page=*/100, /*row=*/99, /*column=*/51, Direction::Vertical, "abc"));



}
