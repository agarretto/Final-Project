#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <cstring>
#include <string>

using namespace std;


//NOTE ON MATH MAJOR - operating under the assumption that student has knowledge through algebra
//NOTE ON SEMESTER OFFERINGS - based off classes offered fall 2016 and spring 2016
//NOTE ON FILE SET UP
//string,int 1,int 2,int 3
//
//string = name of class
//int 1 = number of credits
//int 2 = number of prereqs for this class
//    if int 2 = 0 (no prereqs)
//    if int 2 = 1 (one prereq)
//    etc.
//int 3 = semester being offered
//    if int 3 = 0, class is offered both fall and spring semester
//    if int 3 = 1, class if offered only fall semester
//    if int 3 = 2, class if offered only spring semeseter

struct info {       //struct to hold all the info about the class
    string class_name;
    int credits;
    int pre_reqs;
    int semester;
};

void fall_semester (stack <info>& math_classes, stack<info>& core_classes,stack <info>& wrong_semester, ofstream& out, int corenum);
void spring_semester (stack <info>& math_classes, stack<info>& core_classes,stack <info>& wrong_semester, ofstream& out, int corenum);

int main()
{
    ifstream in;
    in.open ("/Users/andreagarretto/Desktop/COMP271/Class_Schedule/math_major_class_list.txt");
    if(!in.is_open())
    {
        cout << "1Cannot locate file.\n";
    }
    string name, credits, pre_reqs, semester;
    vector <info> math_vector;     //vector of structs to hold class info
    int i = 0;

    while (in.peek()!=EOF)      //read through file, add all the math major info to the vector
    {
        math_vector.push_back(info());
        getline(in,name,',');
        math_vector[i].class_name = name;
        getline(in,credits,',');
        int tmp = stoi(credits);
        math_vector[i].credits = tmp;
        getline(in,pre_reqs,',');
        int tmp1 = stoi(pre_reqs);
        math_vector[i].pre_reqs = tmp1;
        getline(in,semester,',');
        int tmp2 = stoi(semester);
        math_vector[i].semester = tmp2;
        i++;
    }
    in.clear();
    in.close();

    ifstream in2;
    in2.open ("/Users/andreagarretto/Desktop/COMP271/Class_Schedule/core_class_list.txt");
    if(!in2.is_open())
    {
        cout << "2Cannot locate file.\n";
    }

    vector <info> core_vector;     //vector of structs to hold class info
    int j = 0;

    while (in2.peek()!=EOF)      //read through file, add all the class info to the vector
    {
        core_vector.push_back(info());
        getline(in2,name,',');
        core_vector[j].class_name = name;
        getline(in2,credits,',');
        int tmp = stoi(credits);
        core_vector[j].credits = tmp;
        getline(in2,pre_reqs,',');
        int tmp1 = stoi(pre_reqs);
        core_vector[j].pre_reqs = tmp1;
        getline(in2,semester,',');
        int tmp2 = stoi(semester);
        core_vector[j].semester = tmp2;
        j++;
    }

    in2.clear();
    in2.close();

    stack <info> math_classes;   //will hold the math classes from the file


    for (int i = 0; i< math_vector.size() ; i++){ //go through vector
        if (math_vector[i].pre_reqs == 6) {     //go through the vector, find all the classes with 6 prereqs
            info tmp = math_vector[i];
            math_classes.push(tmp);       //push classes with the most prereqs to the bottom of the stack
        }
    }
    for (int i = 0; i< math_vector.size() ; i++){
        if (math_vector[i].pre_reqs == 5) {
            info tmp = math_vector[i];
            math_classes.push(tmp);
        }
    }
    for (int i = 0; i< math_vector.size() ; i++){
        if (math_vector[i].pre_reqs == 4) {
            info tmp = math_vector[i];
            math_classes.push(tmp);
        }
    }
    for (int i = 0; i< math_vector.size() ; i++){
        if (math_vector[i].pre_reqs == 3) {
            info tmp = math_vector[i];
            math_classes.push(tmp);
        }
    }
    for (int i = 0; i< math_vector.size() ; i++){
        if (math_vector[i].pre_reqs == 2) {
            info tmp = math_vector[i];
            math_classes.push(tmp);
        }
    }
    for (int i = 0; i< math_vector.size() ; i++){
        if (math_vector[i].pre_reqs == 1) {
            info tmp = math_vector[i];
            math_classes.push(tmp);
        }
    }
    for (int i = 0; i< math_vector.size() ; i++){
        if (math_vector[i].pre_reqs == 0) {
            info tmp = math_vector[i];
            math_classes.push(tmp);
        }
    }

    stack <info> core_classes; // will hold the core classes from the file

    for (int i = 0; i< core_vector.size() ; i++){
        if (core_vector[i].pre_reqs == 1) {
            info tmp = core_vector[i];
            core_classes.push(tmp);
        }
    }
    for (int i = 0; i< core_vector.size() ; i++){
        if (core_vector[i].pre_reqs == 0) {
            info tmp = core_vector[i];
            core_classes.push(tmp);
        }
    }

//
//    while (!classes.empty()){
//        info tmp = classes.top();
//        cout << tmp.class_name << "  " << tmp.pre_reqs <<endl;
//        classes.pop();
//    }


    ofstream out;
    out.open ("/Users/andreagarretto/Desktop/COMP271/Class_Schedule/4_year_plan.txt");

    stack <info> wrong_semester; //will hold the classes that are being popped off in the wrong semester

    out << "YEAR 1: FALL SEMESTER" << endl;
    fall_semester (math_classes,core_classes,wrong_semester,out,4);
    out << endl;

    out << "YEAR 1: SPRING SEMESTER" <<endl;
    spring_semester(math_classes,core_classes,wrong_semester,out,4);
    out <<endl;



    out << "YEAR 2: FALL SEMESTER" << endl;
    fall_semester (math_classes,core_classes,wrong_semester,out,4);
    out << endl;

    out << "YEAR 2: SPRING SEMESTER" <<endl;
    spring_semester (math_classes,core_classes,wrong_semester,out,4);
    out <<endl;


    out << "YEAR 3: FALL SEMESTER" << endl;
    fall_semester (math_classes,core_classes,wrong_semester,out,2);
    out << endl;


    out << "YEAR 3: SPRING SEMESTER" <<endl;
    spring_semester(math_classes,core_classes,wrong_semester,out,2);
    out << endl;



    out << "YEAR 4: FALL SEMESTER" << endl;
    fall_semester (math_classes,core_classes,wrong_semester,out,2);
    out << endl;


    out << "YEAR 4: SPRING SEMESTER" <<endl;
    spring_semester(math_classes,core_classes,wrong_semester,out,2);
    out <<endl;

  out.clear();
  out.close();

cout << "END OF CODE" <<endl;

    return 0;

}


void fall_semester (stack <info>& math_classes, stack<info>& core_classes,stack <info>& wrong_semester, ofstream& out,int corenum)
{
    int credits = 0;
    while (!wrong_semester.empty()) {       //if any classes were poped off in the wrong semester, they will be added to the schedule first
        info temp = wrong_semester.top();
        out << temp.class_name<< "    " << temp.credits << " credits"  <<endl;
        credits = credits + temp.credits;
        wrong_semester.pop();
    }


    if (!core_classes.empty()){            //if there are still core classes to be taken
        int counter = 0;
        while (counter < corenum) {       //add # core classes spassed in by function till core is done (electives considered core)
            info temp3 = core_classes.top();
            out << temp3.class_name << "    " << temp3.credits<< " credits"  <<endl;
            credits = credits + temp3.credits;
            core_classes.pop();
            counter++;
        }

    }

    while (credits < 15 && !math_classes.empty()) { //while the semester isnt full and there are still courses to add
        info temp2 = math_classes.top();
        if (temp2.semester == 0 || temp2.semester == 1) {       //if the class is offered fall semester or both
            out << temp2.class_name << "    " << temp2.credits<< " credits"  <<endl;
            credits = credits + temp2.credits;
            math_classes.pop();
        }
        else {      //class is only offered in spring
            wrong_semester.push(temp2);  //push class onto the wrong semester class
            math_classes.pop();
        }

    }
    out <<endl;
    out << "Total credits: " << credits <<endl;

}

void spring_semester (stack <info>& math_classes, stack<info>& core_classes,stack <info>& wrong_semester, ofstream& out, int corenum)
{
    int credits = 0;
    info temp;
    while (!wrong_semester.empty()) {       //if any classes were poped off in the wrong semester, they will be added to the schedule first
        temp = wrong_semester.top();
        out << temp.class_name<< "    " << temp.credits << " credits"  <<endl;
        credits = credits + temp.credits;
        wrong_semester.pop();
    }


    if (!core_classes.empty()){            //if there are still core classes to be taken
        int counter = 0;
        while (counter < corenum) {       //add # of core classes passed in (more in early semsters (electives considered core)
            info temp3 = core_classes.top();
            out << temp3.class_name << "    " << temp3.credits<< " credits"  <<endl;
            credits = credits + temp3.credits;
            core_classes.pop();
            counter++;
        }
    }



    while (credits < 15 && !math_classes.empty()){ //add major specific classes till semester is full or the stack is empty
        info temp2 = math_classes.top();
        if (temp2.semester == 0 || temp2.semester == 2) {       //if the class is offered spring semester or both
            out << temp2.class_name << "    " << temp2.credits<< " credits"  <<endl;
            credits = credits + temp2.credits;
            math_classes.pop();
        }
        else {      //class is only offered in spring
            wrong_semester.push(temp2);  //push class onto the wrong semester class
            math_classes.pop();
        }

    }

    out <<endl;
    out << "Total credits: " << credits <<endl;

}
