#define BOOST_TEST_MODULE h_w_five_test_suite
#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>

#include <boost/test/tools/output_test_stream.hpp>

#include "DListT.h"

using boost::test_tools::output_test_stream;
using namespace std;

BOOST_AUTO_TEST_SUITE(h_w_5)

void DataTest(DListT & playlistOne, string data, string error){
    output_test_stream output;

    streambuf * old = cout.rdbuf(output.rdbuf());

    string x = playlistOne.Data();
    //Restore cout
    cout.rdbuf(old);

    BOOST_TEST(x == data);
    BOOST_TEST(output.is_equal(error, false));
    BOOST_TEST(output.check_length(error.size(), false));       
    return;
}

void DataTestNoError(DListT & playlistOne, string data) {
    string x = playlistOne.Data();
    BOOST_TEST(x == data);
    return;
}

void DataPointerTest(DListT & playlist, string home, string right, string left) {
    //Verify data at home, right, and left nodes
	playlist.Home();
    BOOST_TEST(playlist.Data() == home);
    
    playlist.Right();
    BOOST_TEST(playlist.Data() == right);

    playlist.Home();

    playlist.Left();
    BOOST_TEST(playlist.Data() == left);

    return;
}

void CompareLists(DListT & playlist, const vector<string> & other) {
    playlist.Home();
    size_t i;

    if(playlist.Size() != other.size()){
        BOOST_CHECK(playlist.Size() != other.size());
        BOOST_FAIL("Size of the list does not match other list");	
    }

    for(i = 0; i < playlist.Size(); i++) {
		DataTestNoError(playlist, other[i]);
		playlist.Right();
    }

    return;
}

BOOST_AUTO_TEST_CASE(DLCL_CONSTRUCTOR_TEST){
    DListT playlist;
    string errorMessage = "Error: Attempt to access Empty List.\n";
    string data = "NO DATA";
    
    BOOST_TEST(playlist.Size() == 0);
    DataTest(playlist, data, errorMessage);

    playlist.Right();
    DataTest(playlist, data, errorMessage);

    playlist.Home();
    DataTest(playlist, data, errorMessage);

    playlist.Left();
    DataTest(playlist, data, errorMessage);
}

BOOST_AUTO_TEST_CASE(DLCL_SINGLE_INSERT_TEST){
	DListT playlist;
	string data = "Data";
	vector<string> playlistTwo;
	
	playlistTwo.push_back(data);
	playlist.Insert(data);
	//List should now contain: Data
	
	CompareLists(playlist, playlistTwo);

    BOOST_TEST(playlist.Size() == 1);
	DataPointerTest(playlist, "Data", "Data", "Data");
}

BOOST_AUTO_TEST_CASE(DLCL_MANY_INSERT_FRONT_TEST){
	DListT playlist;
	vector<string> mainList;
	vector<string> testList{"A", "B", "C", "D", "E"};
	
	for (auto i: testList){
		playlist.Home();
		playlist.Insert(i);
		 
		mainList.insert(mainList.begin(), i);

		CompareLists(playlist, mainList);		
	}	
}

BOOST_AUTO_TEST_CASE(DLCL_INSERT_MANY_TEST){
	DListT playlist;
	vector<string> mainList;
	
	playlist.Insert("2");
	playlist.Insert("1");
	
	mainList.push_back("1");
	mainList.push_back("2");
	//Lists should contain: 1 2
	CompareLists(playlist, mainList);
	
	//Insert at second position
	playlist.Home();
	playlist.Right();
	playlist.Insert("3");
	//Check current
	DataTestNoError(playlist, "3");
	
	mainList.insert(begin(mainList)+1,"3");
	CompareLists(playlist, mainList);
    //List should now contain: 1 3 2	
	playlist.Home();
	playlist.Right(); //Point to 3
	playlist.Right(); //Point to 2
	playlist.Insert("4");
	//List should now contain: 1 3 4 2
	
	DataTestNoError(playlist, "4");
	mainList.insert(begin(mainList)+2, "4");
	CompareLists(playlist, mainList);
	
	//Insert at middle
	playlist.Home();
	playlist.Right(); //Point to 3
	playlist.Right(); //Point to 4
	playlist.Insert("5");
	mainList.insert(begin(mainList)+2, "5");
	CompareLists(playlist, mainList);
	//List should now contain 1 3 5 4 2
	
	//Insert at front
	playlist.Home();
	playlist.Insert("A");
	DataTestNoError(playlist, "A");
	mainList.insert(begin(mainList), "A");
	CompareLists(playlist, mainList);	
	//List should now contain A 1 3 5 4 2
}

BOOST_AUTO_TEST_CASE(DLCL_RANDOM_INSERT_TEST){
	DListT playlist;
	vector<string> testData{"3", "4", "5", "6", "7", "8", "9", "10"};
	vector<string> mainList{"1", "2"};
	
	size_t pos;
	size_t i;
	
	playlist.Insert("2");
	playlist.Insert("1");
	CompareLists(playlist, mainList);
	
	srand(0);
	
	for(auto x: testData){
		pos = rand()%mainList.size();
		
		playlist.Home();
		for(i = 0; i < pos; i++){
			playlist.Right();
		}
		playlist.Insert(x);
		//Verify current
		DataTestNoError(playlist, x);
		
		mainList.insert(begin(mainList)+pos, x);
		
		CompareLists(playlist, mainList);
	}	
	
}

BOOST_AUTO_TEST_CASE(DLCL_SINGLE_INSERT_AFTER){
	DListT playlist;
	string data = "Data";
	vector<string> playlistTwo;
	
	playlistTwo.push_back(data);
	playlist.InsertAfter(data);
	//List should now contain: Data
	
	CompareLists(playlist, playlistTwo);

    BOOST_TEST(playlist.Size() == 1);
	DataPointerTest(playlist, "Data", "Data", "Data");	
}

BOOST_AUTO_TEST_CASE(DLCL_MANY_INSERT_AFTER_FRONT_TEST){
	DListT playlist;
	vector<string> mainList;
	vector<string> testList{"A", "B", "C", "D", "E"};
	
	playlist.Home();
	playlist.InsertAfter(testList[0]);
	mainList.insert(mainList.begin(), testList[0]);
	CompareLists(playlist, mainList);
	//Insert first node
	
	for (size_t i = 1; i < testList.size(); i++){
		playlist.Home();
		playlist.InsertAfter(testList[i]);
		 
		mainList.insert(mainList.begin()+1, testList[i]);

		CompareLists(playlist, mainList);		
	}	
	//Lists should now contain: A E D C B
}


BOOST_AUTO_TEST_CASE(DLCL_INSERT_AFTER_MANY_TEST){
	DListT playlist;
	vector<string> mainList;
	
	playlist.InsertAfter("1");
	playlist.InsertAfter("2");
	
	mainList.push_back("1");
	mainList.push_back("2");
	//Lists should contain: 1 2
	CompareLists(playlist, mainList);
	
	//Insert at second position
	playlist.Home();
	playlist.Right();
	playlist.InsertAfter("3");
	//Check current
	DataTestNoError(playlist, "3");
	
	mainList.push_back("3");
	CompareLists(playlist, mainList);
    //List should now contain: 1 2 3	
	playlist.Home();
	playlist.Right(); //Point to 2
	playlist.Right(); //Point to 3
	playlist.InsertAfter("4");
	//List should now contain: 1 2 3 4
	
	DataTestNoError(playlist, "4");
	mainList.push_back("4");
	CompareLists(playlist, mainList);
	
	//Insert at middle
	playlist.Home();
	playlist.Right(); //Point to 2
	playlist.Right(); //Point to 3
	playlist.InsertAfter("5");
	mainList.insert(begin(mainList)+3, "5");
	CompareLists(playlist, mainList);
	//List should now contain 1 2 3 5 4
	
	//Insert at front
	playlist.Home();
	playlist.InsertAfter("A");
	DataTestNoError(playlist, "A");
	mainList.insert(begin(mainList)+1, "A");
	CompareLists(playlist, mainList);	
	//Lists should now contain 1 A 2 3 5 4
}

BOOST_AUTO_TEST_CASE(DLCL_RANDOM_INSERT_AFTER_TEST){
	DListT playlist;
	vector<string> testData{"3", "4", "5", "6", "7", "8", "9", "10"};
	vector<string> mainList{"1", "2"};
	
	size_t pos;
	size_t i;
	
	playlist.InsertAfter("1");
	playlist.InsertAfter("2");
	CompareLists(playlist, mainList);
	
	srand(0);
	
	for(auto x: testData){
		pos = rand()%mainList.size();
		
		playlist.Home();
		for(i = 0; i < pos; i++){
			playlist.Right();
		}
		playlist.InsertAfter(x);
		//Verify current
		DataTestNoError(playlist, x);
		
		mainList.insert(begin(mainList)+pos+1, x);
		
		CompareLists(playlist, mainList);
	}	
	
}

BOOST_AUTO_TEST_CASE(DLCL_DELETE_EMPTY_TEST){
    DListT playlist; 
    output_test_stream output;
    string errorMessage = "Error: Attempt to delete in an Empty List.\n";
   
    streambuf * old = cout.rdbuf(output.rdbuf());
    
    playlist.Delete();

    cout.rdbuf(old);

    BOOST_TEST(output.is_equal(errorMessage, false));
    BOOST_TEST(output.check_length(errorMessage.size(), false));
}

BOOST_AUTO_TEST_CASE(DLCL_DELETE_SINGLE_NODE){
    DListT playlist;
    string data = "NO DATA";
    string errorMessage = "Error: Attempt to access Empty List.\n";
    
    playlist.Insert("A");
	//List should be: A
    BOOST_TEST(playlist.Size() == 1);

    playlist.Delete();
	//List should now be empty
    BOOST_TEST(playlist.Size() == 0);
   
    DataTest(playlist, data, errorMessage);
}

BOOST_AUTO_TEST_CASE(DLCL_DELETE_HEAD_TWO_NODES){
    DListT playlist;
   
    playlist.Insert("A");
    playlist.Insert("B");
	//List should be: B A
    BOOST_TEST(playlist.Size() == 2);
    
	playlist.Delete(); 
    //List should now be: A	
	BOOST_TEST(playlist.Size() == 1);

    DataPointerTest(playlist, "A", "A", "A");
}

BOOST_AUTO_TEST_CASE(DLCL_DELETE_HEAD_TWO_PLUS_NODES){
	DListT playlist;
	
	playlist.Insert("A");
	playlist.Insert("B");
	playlist.Insert("C");
	//List should be: C B A
	BOOST_TEST(playlist.Size() == 3);
	
	playlist.Delete();
	//List should now be: B A
	BOOST_TEST(playlist.Size() == 2);
	
	DataPointerTest(playlist, "B", "A", "A");
}

BOOST_AUTO_TEST_CASE(DLCL_DELETE_SECOND_NODE_TWO_NODES){
	DListT playlist;
	
	playlist.Insert("A");
	playlist.Insert("B");
	//List should be: B A
	BOOST_TEST(playlist.Size() == 2);
	
	playlist.Right();
	playlist.Delete();
	//List should now be: B
	BOOST_TEST(playlist.Size() == 1);
	
	DataPointerTest(playlist, "B", "B", "B");	
}

BOOST_AUTO_TEST_CASE(DLCL_DELETE_IN_BIGGER_LIST_NOT_HEAD){
	DListT playlist;
	
	playlist.InsertAfter("A");
	playlist.InsertAfter("B");
	playlist.InsertAfter("C");
	playlist.InsertAfter("D");
	playlist.InsertAfter("E");
	playlist.InsertAfter("F");
	playlist.InsertAfter("G");
	playlist.InsertAfter("H");
	//Lists should be: A B C D E F G H
	BOOST_TEST(playlist.Size() == 8);
	
	playlist.Home(); //Current should point at A
	playlist.Right();//Current should point at B
    playlist.Right();//Current should point at C
    playlist.Right();//Current should point at D
	
	playlist.Delete();
	//List should now be: A B C E F G H
	playlist.Home(); //Current should point at A
	playlist.Right();//Current should point at B
    playlist.Right();//Current should point at C
    playlist.Right();//Current should point at E
	
	BOOST_TEST(playlist.Data() == "E");
	playlist.Left(); //Current should point at C
	BOOST_TEST(playlist.Data() == "C");
	BOOST_TEST(playlist.Size() == 7);
}

BOOST_AUTO_TEST_CASE(DLCL_DELETE_TAIL) {
	DListT playlist;
	
	playlist.InsertAfter("A");
	playlist.InsertAfter("B");
	playlist.InsertAfter("C");
	//List should now be: A B C
	BOOST_TEST(playlist.Size() == 3);
	
	playlist.Delete();
	BOOST_TEST(playlist.Size() == 2);
	//List should now contain: A B
	DataPointerTest(playlist, "A", "B", "B");		
}

BOOST_AUTO_TEST_CASE(DLCL_OVERLOAD_ASSIGNMENT_TEST_EMPTY){
	DListT playlist, playlistTwo;
	string tempData;
	string errorMessage = "Error: Attempt to access Empty List.\n";
	output_test_stream output;

	//Testing copying empty playlist
	BOOST_TEST(playlist.Size() == 0);
	playlist = playlistTwo;
	BOOST_TEST(playlist.Size() == playlistTwo.Size());
	
	streambuf * old = cout.rdbuf(output.rdbuf());
	tempData = playlistTwo.Data();
	cout.rdbuf(old);
	BOOST_TEST(output.is_equal(errorMessage, false));
	
	DataTest(playlist, tempData, errorMessage);	
}

BOOST_AUTO_TEST_CASE(DLCL_OVERLOAD_ASSIGNMENT_COPY_FULL_TO_EMPTY){
	DListT playlist, playlistTwo;
	string tempData;
	string errorMessage = "Error: Attempt to access Empty List.\n";
	output_test_stream output;
	
	
	playlist.InsertAfter("A");
	playlist.InsertAfter("B");
	playlist.InsertAfter("C");
	playlist.InsertAfter("D");
	playlist.InsertAfter("E");
	BOOST_TEST(playlist.Size() == 5);
	BOOST_TEST(playlistTwo.Size() == 0);
	//Copy empty to full using overloaded assignment operator
	playlist = playlistTwo;
	BOOST_TEST(playlist.Size() == playlistTwo.Size());
	
	streambuf * old = cout.rdbuf(output.rdbuf());
	tempData = playlistTwo.Data();
	cout.rdbuf(old);
	BOOST_TEST(output.is_equal(errorMessage, false));
	
	DataTest(playlist, tempData, errorMessage);	
}

BOOST_AUTO_TEST_CASE(DLCL_OVERLOAD_ASSIGNMENT_COPY_EMPTY_TO_FULL){
	DListT playlist, playlistTwo;
	vector<string> copy;
	
	//Test copying one element
	BOOST_TEST(playlist.Size() == 0);
	playlistTwo.Insert("A");
	copy.push_back("A");
	playlist = playlistTwo;
	CompareLists(playlist, copy);
	DataPointerTest(playlist, "A", "A", "A");
	
	//Test copying two elements
	BOOST_TEST(playlist.Size() == 1);
	playlistTwo.InsertAfter("B");
	copy.push_back("B");
	playlist = playlistTwo;
	CompareLists(playlist, copy);
	DataPointerTest(playlist, "A", "B", "B");
	
	//Test copying many elements
	BOOST_TEST(playlist.Size() == 2);
	playlistTwo.InsertAfter("C");
	playlistTwo.InsertAfter("D");
	playlistTwo.InsertAfter("E");
	playlistTwo.InsertAfter("F");
	playlistTwo.InsertAfter("G");
	copy.push_back("C");
	copy.push_back("D");
	copy.push_back("E");
	copy.push_back("F");
	copy.push_back("G");
	playlist = playlistTwo;
	CompareLists(playlist, copy);
	DataPointerTest(playlist, "A", "B", "G");		
}

BOOST_AUTO_TEST_CASE(DLCL_OVERLOAD_ASSIGNMENT_TEST_SAME_COPY){
	DListT playlist;
	
	playlist.InsertAfter("A");
	playlist.InsertAfter("B");
	playlist.InsertAfter("C");
	//List should contain A B C
	BOOST_TEST(playlist.Data() == "C");
	
	playlist = playlist;
	BOOST_TEST(playlist.Data() == "C");
	//List should return * this
	DataPointerTest(playlist, "A", "B", "C");			
}

BOOST_AUTO_TEST_CASE(DLCL_OVERLOAD_ASSIGNMENT_CURRENT_CHECK){
    DListT playlist, playlistOne, playlistTwo, playlistMany, playlistTail;
	
	playlist.Insert("A");
	//List should contain A
	BOOST_TEST(playlist.Data() == "A");
	playlistOne = playlist;
	//Testing current with one node
	BOOST_TEST(playlistOne.Data() == "A");
	//Clear playlist
	
	playlist.InsertAfter("B");
	//List should contain A B
	playlist.Home();
	playlist.Right();//Should point to B
	BOOST_TEST(playlist.Data() == "B");
	playlistTwo = playlist;
	//Testing current with two nodes
	BOOST_TEST(playlistTwo.Data() == "B");
	//Clear playlist
	playlist.Delete();
	playlist.Delete();

    playlist.InsertAfter("A");
    playlist.InsertAfter("B");
    playlist.InsertAfter("C");
    playlist.InsertAfter("D");
    playlist.InsertAfter("E");
    //List should contain A B C D E 

    playlist.Home();
    playlist.Right();//Point at B
    playlist.Right();//Point at C
    playlist.Right();//Point at D
	BOOST_TEST(playlist.Data() == "D");
    playlistMany = playlist;
	BOOST_TEST(playlistMany.Data() == "D");
	
	playlist.Right();//Point to E
	BOOST_TEST(playlist.Data() == "E");
	//Testing current at tail
	playlistTail = playlist;
	BOOST_TEST(playlistTail.Data() == "E");
}

BOOST_AUTO_TEST_CASE(DLCL_COPY_CONSTRUCTOR_TEST_EMPTY){
	DListT playlist;
	string tempData;
	string errorMessage = "Error: Attempt to access Empty List.\n";
	output_test_stream output;

	//Testing copying empty playlist
	BOOST_TEST(playlist.Size() == 0);
	DListT playlistTwo(playlist);
	BOOST_TEST(playlist.Size() == playlistTwo.Size());
	
	streambuf * old = cout.rdbuf(output.rdbuf());
	tempData = playlistTwo.Data();
	cout.rdbuf(old);
	BOOST_TEST(output.is_equal(errorMessage, false));
	
	DataTest(playlist, tempData, errorMessage);	
}

BOOST_AUTO_TEST_CASE(DLCL_COPY_CONSTRUCTOR_COPY_EMPTY_TO_FULL){
	DListT playlist;
	vector<string> copy;
	
	//Test copying one element
	BOOST_TEST(playlist.Size() == 0);
	playlist.Insert("A");
	copy.push_back("A");
	DListT playlistOne(playlist);
	CompareLists(playlistOne, copy);
	DataPointerTest(playlistOne, "A", "A", "A");
	
	//Test copying two elements
	BOOST_TEST(playlist.Size() == 1);
	playlist.InsertAfter("B");
	copy.push_back("B");
	DListT playlistTwo(playlist);
	CompareLists(playlistTwo, copy);
	DataPointerTest(playlistTwo, "A", "B", "B");
	
	//Test copying many elements
	BOOST_TEST(playlist.Size() == 2);
	playlist.InsertAfter("C");
	playlist.InsertAfter("D");
	playlist.InsertAfter("E");
	playlist.InsertAfter("F");
	playlist.InsertAfter("G");
	copy.push_back("C");
	copy.push_back("D");
	copy.push_back("E");
	copy.push_back("F");
	copy.push_back("G");
	DListT playlistMany(playlist);
	CompareLists(playlistMany, copy);
	DataPointerTest(playlistMany, "A", "B", "G");		
}

BOOST_AUTO_TEST_CASE(DLCL_COPY_CONSTRUCTOR_CURRENT_CHECK){
    DListT playlist;
	
	playlist.Insert("A");
	//List should contain A
	BOOST_TEST(playlist.Data() == "A");
	DListT playlistOne(playlist);
	//Testing current with one node
	BOOST_TEST(playlistOne.Data() == "A");
	//Clear playlist
	
	playlist.InsertAfter("B");
	//List should contain A B
	playlist.Home();
	playlist.Right();//Should point to B
	BOOST_TEST(playlist.Data() == "B");
	DListT playlistTwo(playlist);
	//Testing current with two nodes
	BOOST_TEST(playlistTwo.Data() == "B");
	//Clear playlist
	playlist.Delete();
	playlist.Delete();

    playlist.InsertAfter("A");
    playlist.InsertAfter("B");
    playlist.InsertAfter("C");
    playlist.InsertAfter("D");
    playlist.InsertAfter("E");
    //List should contain A B C D E 

    playlist.Home();
    playlist.Right();//Point at B
    playlist.Right();//Point at C
    playlist.Right();//Point at D
	BOOST_TEST(playlist.Data() == "D");
    DListT playlistMany(playlist);
	BOOST_TEST(playlistMany.Data() == "D");
	
	playlist.Right();//Point to E
	BOOST_TEST(playlist.Data() == "E");
	//Testing current at tail
	DListT playlistTail(playlist);
	BOOST_TEST(playlistTail.Data() == "E");
}


BOOST_AUTO_TEST_SUITE_END()
