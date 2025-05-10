#include<iostream>
using namespace std;



class Course{
    string name;
    float creditHour;
    public:
    Course(){
        name="";
        creditHour=0.0;
    }
    Course (string name, float creditHour){
        this->name=name;
        this->creditHour=creditHour;
    }
    string getName(){
        return name;
    }
    float getCreditHour(){
        return creditHour;
    }
    void setName(string name){
        this->name=name;
    }
    void  setCreditHour(float  creditHour){
        this->creditHour=creditHour;
    }
    void display(){
        cout<<name<<" "<<creditHour<<endl;
    }

};

class Student{
    string name;
    int id;
    Course* courses;
    int totalCourses;
    int maxCourses;
    float* gradepoints;
    public:
    Student(){
        name="";
        maxCourses=0;
        id=0;
        totalCourses=0;
    }
    Student(string  name,  int  id,  int maxCourses){
        this->name=name;
        this->id=id;
        this->maxCourses=maxCourses;
        courses= new Course[maxCourses];
        gradepoints=new float[maxCourses];
        totalCourses=0;

    }
    Student(const Student& a){
        name = a.name;
        id=a.id;
        maxCourses=a.maxCourses;
        totalCourses=a.totalCourses;
        courses= new Course[maxCourses];
        gradepoints=new float[maxCourses];
        for(int i=0;i<totalCourses;i++){
            courses[i]=a.courses[i];
            gradepoints[i]=a.gradepoints[i];
        }
    }
    ~Student() {
    delete[] courses;
    delete[] gradepoints;
    }

    void setName(string name){
        this->name=name;
    }
    void setId(int id){
        this->id=id;
    }
    void  setInfo(string  name,  int  id){
        this->name=name;
        this->id=id;
    }
    void  addCourse(Course  c){
        if(totalCourses>=maxCourses) return;

            courses[totalCourses]=c;
            gradepoints[totalCourses]=0.0;
            totalCourses++;
    
    }
    void  addCourse(Course  course,  float  gradePoint){
        if(totalCourses>=maxCourses)return;
        courses[totalCourses]=course;
        gradepoints[totalCourses]=gradePoint;
        totalCourses++;
    }
    void  setGradePoint (Course  c,  float  gradePoint)
    {
        for(int i=0;i<totalCourses;i++)
        {
            if(courses[i].getName()==c.getName() && courses[i].getCreditHour()==courses[i].getCreditHour()){
                gradepoints[i]=gradePoint;
            }
        }
    }
    void  setGradePoint (float*  gradePoints,  int  n){
        for(int i=0;i<n;i++){
            gradepoints[i]=gradePoints[i];
        }
    }
    string getName(){
        return name;
    }
    float  getCGPA(){
        float cg=0;
        float totalcredit=0;
        for(int i=0;i<totalCourses;i++){
            cg+=gradepoints[i]*courses[i].getCreditHour();
            totalcredit+=courses[i].getCreditHour();
        }
        if(totalcredit==0)return 0.0;
        float CGPA=cg/totalcredit;
        return CGPA;
    }

    float  getGradePoint (Course  c){
        int idx=-1;
        for(int i=0;i<totalCourses;i++)
        {
            if(courses[i].getName()==c.getName() && courses[i].getCreditHour()==c.getCreditHour()){
                idx=i;
            }
        }
        // if(idx==-1) return;
        return gradepoints[idx];
    }

    int  getTotalCourses(){
        return totalCourses;
    }
    float  getTotalCreditHours(){

        float totalcredit=0.0;
        for(int i=0;i<totalCourses;i++){
            totalcredit+=courses[i].getCreditHour();
        }
        return totalcredit;
    }

    Course  getMostFavoriteCourse(){
        float max=gradepoints[0];
        int idx=0;
        for(int i=0;i<totalCourses;i++){
            if(max<gradepoints[i]){
                max=gradepoints[i];
                idx=i;
            }
        }
        return courses[idx];
    }
    Course  getLeastFavoriteCourse(){
        float min=gradepoints[0];
        int idx=0;
        for(int i=0;i<totalCourses;i++){
            if(min>gradepoints[i]){
                min=gradepoints[i];
                idx=i;
            }
        }
        return courses[idx];
    }

    Course*  getFailedCourses(int  &count){
        count=0;
        for(int i=0;i<totalCourses;i++){
            if(gradepoints[i]<2.0)count++;
        }
        if(!count) return NULL;
        Course* failed= new Course[count];
        int j=0;
        for(int i=0;i<totalCourses;i++){
            if(gradepoints[i]<2.0)
            {
                failed[j++]=courses[i];
            }
        }
        return failed;
    }
    void  display(){
        cout<<"Student Name: "<<name<<"ID: "<<id<<endl;
        for(int i=0;i<totalCourses;i++){
            cout<<"Course Name: "<<courses[i].getName()<<"' "<<"Credit Hour: "<<courses[i].getCreditHour();
            cout<<"' "<<"gradePoint: "<<gradepoints[i]<<endl; 
        }
        cout<<"CGPA: "<<getCGPA()<<endl;
        cout<<"Total Credit Hours Earned: "<<getTotalCreditHours()<<endl;
        cout<<"Most Favourite Course :"<<getMostFavoriteCourse().getName()<<endl;
        cout<<"Least Favourite Course :"<<getLeastFavoriteCourse().getName()<<endl;
        cout<<"================================== "<<endl;
        cout<<"================================== "<<endl;

    }


};

const int Max_students=100;
int totalStudents=0;
Student* students [Max_students];

Student getTopper(){
    float max= students[0]->getCGPA();
    int idx=0;
    for(int i=0;i<totalStudents;i++)
    {
        if(max<students[i]->getCGPA())
        {
            max=students[i]->getCGPA();
            idx=i;
        }
    }
    return *students[idx];
}


Student  getTopper(Course  c){
    float max=students[0]->getGradePoint(c);
    int idx=0;
    for(int i=0;i<totalStudents;i++)
    {
        if(max<students[i]->getGradePoint(c))
        {
            max=students[i]->getGradePoint(c);
            idx=i;
        }
    }
    return *students[idx];
}



int main(){
    // generate courses 
const int COURSE_COUNT = 6; 
Course courses[COURSE_COUNT] = { 
Course("CSE107", 3), 
Course("CSE105", 3), 
Course("CSE108", 1.5), 
Course("CSE106", 1.5), 
Course("EEE164", 0.75), 
Course("ME174", 0.75), 
}; 
float gradePoints[COURSE_COUNT] = {4.0, 4.0, 3.5, 3.5, 4.0, 3.25}; 
// generate students 
Student s1 = Student("Sheldon", 1, 5); 
students[totalStudents++] = &s1; 
// add courses to s1 
s1.addCourse(courses[0]); 
s1.addCourse(courses[1]); 
s1.addCourse(courses[2]); 
s1.addCourse(courses[3]); 
s1.addCourse(courses[4]); 
s1.addCourse(courses[5]); 
s1. setGradePoint (gradePoints, s1.getTotalCourses()); 
s1.display(); 
Student s2 = Student("Penny", 2, 5); 
students[totalStudents++] = &s2; 
s2.addCourse(courses[0]); 
s2.addCourse(courses[2]); 
s2.addCourse(courses[5]); 
s2. setGradePoint (gradePoints, s2.getTotalCourses()); 
s2. setGradePoint (courses[0], 3.25); 
s2.display(); 
Student s3 = s2; 
students[totalStudents++] = &s3; 
s3.setName("Leonard"); 
s3.setId(3); 
s3. setGradePoint (gradePoints, s3.getTotalCourses()); 
s3.addCourse(courses[1], 3.75); 
s3.display(); 
Student s4 = s3; 
students[totalStudents++] = &s4; 
s4.setInfo("Howard", 4); 
s4. setGradePoint (gradePoints, s4.getTotalCourses()); 
s4.addCourse(courses[3], 3.75); 
s4.display(); 
Student s5 = s4; 
students[totalStudents++] = &s5; 
s5.setInfo("Raj", 5); 
s5. setGradePoint (gradePoints, s5.getTotalCourses()); 
s5. setGradePoint (courses[0], 1.5); 
s5. setGradePoint (courses[2], 2.0); 
s5. setGradePoint (courses[5], 1.75); 
s5. setGradePoint (courses[3], 3.75); 
s5.display(); 
int failedCount; 
Course* failedCourses = s5.getFailedCourses(failedCount); 
cout << "Failed Courses for " << s5.getName() << ":" << endl; 
for (int i = 0; i < failedCount; ++i) { 
failedCourses[i].display(); 
cout << endl; 
} 
delete[] failedCourses; 
cout << "==================================" << endl; 
Student topper = getTopper(); 
cout << "Topper: " << topper.getName() << endl; 
cout << "Topper CGPA: " << topper.getCGPA() << endl; 
cout << "==================================" << endl; 
for (int i = 0; i < COURSE_COUNT; ++i) { 
Course c = courses[i]; 
Student topperInCourse = getTopper(c); 
cout << "Topper in " << c.getName() << ": " << 
topperInCourse.getName() << endl; 
cout << "Topper in " << c.getName() << " gradePoint: " << 
topperInCourse. getGradePoint (c) << endl; 
cout << "==================================" << endl; 
} 
return 0;
}