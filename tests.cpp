   #include "header.h"
   #include <gtest/gtest.h>


   namespace my {
namespace project {
namespace {

// The fixture for testing class Foo.
class FooTest : public testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  FooTest() {
        while (!globalstack.empty()) {
            globalstack.pop();
        }

        dictStack.clear();
        functionMap.clear();
        dictmap.clear();
        currentDictStack = 0;
        staticvar = false;

        populate_function_map();
     // You can do set-up work for each test here.
  }

  ~FooTest() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
    
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};
TEST_F(FooTest, orTesting){


    string s1 = "TRUE TRUE or";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "TRUE");

    parsing("TRUE FALSE or");
    ASSERT_EQ(globalstack.top(), "TRUE");

    parsing("FALSE FALSE and");
    ASSERT_EQ(globalstack.top(), "FALSE");

}

TEST_F(FooTest, notTesting){


    string s1 = "TRUE not";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "FALSE");

    parsing("FALSE not");
    ASSERT_EQ(globalstack.top(), "TRUE");


}

TEST_F(FooTest, andTesting){


    string s1 = "TRUE TRUE and";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "TRUE");

    parsing("TRUE FALSE and");
    ASSERT_EQ(globalstack.top(), "FALSE");

    parsing("FALSE FALSE and");
    ASSERT_EQ(globalstack.top(), "FALSE");

}

TEST_F(FooTest, ltTesting){


    string s1 = "1 1 lt";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "FALSE");

    parsing("2 1 lt");
    ASSERT_EQ(globalstack.top(), "FALSE");

    parsing("1 2 lt");
    ASSERT_EQ(globalstack.top(), "TRUE");

}

TEST_F(FooTest, leTesting){


    string s1 = "1 1 le";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "TRUE");

    parsing("1 2 le");
    ASSERT_EQ(globalstack.top(), "TRUE");
    s1 = "2 1 le";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "FALSE");

}
TEST_F(FooTest, gtTesting){


    string s1 = "1 1 gt";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "FALSE");

    parsing("2 1 gt");
    ASSERT_EQ(globalstack.top(), "TRUE");

}


TEST_F(FooTest, geTesting){


    string s1 = "1 1 ge";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "TRUE");

    parsing("1 2 ge");
    ASSERT_EQ(globalstack.top(), "FALSE");
    s1 = "2 1 ge";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "TRUE");

}
TEST_F(FooTest, neTesting){


    string s1 = "1 1 ne";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "FALSE");

    parsing("1 2 ne");
    ASSERT_EQ(globalstack.top(), "TRUE");

}

TEST_F(FooTest, eqTesting){


    string s1 = "1 1 eq";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "TRUE");

    parsing("1 2 eq");
    ASSERT_EQ(globalstack.top(), "FALSE");

}


TEST_F(FooTest, countTesting){


    string s1 = "count";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "0");
    globalstack.pop();

    parsing("1 2 count");
    ASSERT_EQ(globalstack.top(), "2");

}


TEST_F(FooTest, clearTesting){


    string s1 = "1 2 3 4";
    parsing(s1);
    parsing("clear");
    ASSERT_TRUE(globalstack.empty());

    parsing("clear");
    ASSERT_TRUE(globalstack.empty());




}

TEST_F(FooTest, dupTesting){


    string s1 = "1 dup";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "1");
    ASSERT_EQ(globalstack.size(), 2);

     s1 = "(string) dup";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "( string )");
    globalstack.pop();
    ASSERT_EQ(globalstack.top(), "( string )");



}


TEST_F(FooTest, copyTesting){


    string s1 = "1 2 2 copy";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "2");
    ASSERT_EQ(globalstack.size(), 4);

     s1 = "(string) 1 copy";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "( string )");
    globalstack.pop();
    ASSERT_EQ(globalstack.top(), "( string )");



}


TEST_F(FooTest, popTesting){


    string s1 = "1 pop";
    parsing(s1);
    ASSERT_TRUE(globalstack.empty());

    s1 = "pop";
    parsing(s1);
    ASSERT_TRUE(globalstack.empty());

    s1 = "1 2 pop";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "1");


}


TEST_F(FooTest, exchTesting){


    string s1 = "1 2 exch";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "1");

    s1 = "1 exch";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "1");




}


TEST_F(FooTest, setintervalTesting){


    string s1 = "(string) 1 (wow) putinterval";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "swowng");

    s1 = "[string] 3 (str) putinterval";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "swowng");




}

TEST_F(FooTest, getintervalTesting){


    string s1 = "(string) 1 4 getinterval";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "trin");

    s1 = "[string] 3 2 getinterval";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "trin");




}


TEST_F(FooTest, getTesting){


    string s1 = "(string) 3 get";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "105");

    s1 = "[string] 3 get";
    parsing(s1);
    ASSERT_EQ(globalstack.top(), "[ string ]");




}

TEST_F(FooTest, defTesting){


    string s1 = "/add1 {1 add} def";
    parsing(s1);
    s1 = "1 add1";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()), 2);

    s1 = "/number 4 def";
    parsing(s1);
    s1 = "number add1";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()), 5);




}


TEST_F(FooTest, endTesting){


    string s1 = "5 dict begin";
    parsing(s1);
    ASSERT_GT(dictStack.size(), 1);
    ASSERT_EQ(stoi(dictStack[0]["SIZE_OF_DICTIONARY"]), 5);

    parsing("end");
    ASSERT_EQ(dictStack.size(), 1);


    s1 = "5 5 end";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()), 5);
    

}

TEST_F(FooTest, beginTesting){


    string s1 = "5 dict begin";
    parsing(s1);
    ASSERT_GT(dictStack.size(), 1);
    ASSERT_EQ(stoi(dictStack[0]["SIZE_OF_DICTIONARY"]), 5);
    
    s1 = "5 5 begin";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()), 5);
    

}



TEST_F(FooTest, maxlengthTesting){


    string s1 = "5 dict maxlength";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()), 5);


    

}


TEST_F(FooTest, lengthTesting){

    string s1 = "(string) length";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),6);

    s1 = "-2.6 length";
    parsing(s1);
    ASSERT_EQ(globalstack.top(),"-2.6");

    s1 = "5 dict length";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()), 0);


    

}


TEST_F(FooTest, dictTesting){

    string s1 = "5 dict";
    parsing(s1);
    ASSERT_EQ(globalstack.top(),"*5*");

     s1 = "(string) dict";
    parsing(s1);
    ASSERT_EQ(globalstack.top(),"( string )");
    

}


TEST_F(FooTest, sqrtTesting){

    string s1 = "4 sqrt";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),2);

     s1 = "(string) sqrt";
    parsing(s1);
    ASSERT_EQ(globalstack.top(),"( string )");
    

}

TEST_F(FooTest, roundTesting){

    string s1 = "2.6 round";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),3);

    s1 = "2.4 round";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),2);


     s1 = "(string) neg";
    parsing(s1);
    ASSERT_EQ(globalstack.top(),"( string )");
    

}

TEST_F(FooTest, floorTesting){

    string s1 = "2.6 floor";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),2);

    s1 = "-2.6 floor";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),-3);


     s1 = "(string) floor";
    parsing(s1);
    ASSERT_EQ(globalstack.top(),"( string )");
    

}


TEST_F(FooTest, ceilTesting){

    string s1 = "2.6 ceiling";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),3);

    s1 = "-2.6 ceiling";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),-2);


     s1 = "(string) ceiling";
    parsing(s1);
    ASSERT_EQ(globalstack.top(),"( string )");
    

}



TEST_F(FooTest, negTesting){

    string s1 = "-2 neg";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),2);

    s1 = "2 neg";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),-2);


     s1 = "(string) neg";
    parsing(s1);
    ASSERT_EQ(globalstack.top(),"( string )");
    

}



TEST_F(FooTest, absTesting){

    string s1 = "-2 abs";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),2);

    s1 = "2 abs";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),2);


     s1 = "(string) abs";
    parsing(s1);
    ASSERT_EQ(globalstack.top(),"( string )");
    

}




TEST_F(FooTest, modTesting){

    string s1 = "3 2 mod";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),1);


     s1 = "(string) mod";
    parsing(s1);
    ASSERT_EQ(globalstack.top(),"( string )");
    

}


TEST_F(FooTest, idivTesting){

    string s1 = "6 3 idiv";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),2);

     s1 = " 2 idiv";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),1);

     s1 = "(string) idiv";
    parsing(s1);
    ASSERT_EQ(globalstack.top(),"( string )");
    

}

TEST_F(FooTest, divTesting){

    string s1 = "6 3 div";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),2);

     s1 = " 2 div";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),1);

     s1 = "(string) div";
    parsing(s1);
    ASSERT_EQ(globalstack.top(),"( string )");
    

}

TEST_F(FooTest, mulTesting){

    string s1 = "1 2 mul";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),2);

     s1 = " 2 mul";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),4);

     s1 = "(string) mul";
    parsing(s1);
    ASSERT_EQ(globalstack.top(),"( string )");
    

}

TEST_F(FooTest, subTesting){

    string s1 = "1 2 sub";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),-1);

     s1 = " 2 sub";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),-3);

     s1 = "(string) sub";
    parsing(s1);
    ASSERT_EQ(globalstack.top(),"( string )");
    

}


TEST_F(FooTest, addTesting){

    string s1 = "1 2 add";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),3);

     s1 = " 2 add";
    parsing(s1);
    ASSERT_EQ(stoi(globalstack.top()),5);

     s1 = "(string) add";
    parsing(s1);
    ASSERT_EQ(globalstack.top(),"( string )");
    

}
// Tests that the Foo::Bar() method does Abc.


}  // namespace
}  // namespace project
}  // namespace my

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
