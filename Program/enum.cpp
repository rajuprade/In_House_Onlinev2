#include <iostream>
using namespace std;
 
enum system_names { abc,servo,sigcon,sentinel,correlator};
enum class_level { Freshman, Sophomore, Junior, Senior, Drop_Out, Graduate };
enum sport_teams { Football, Basketball, Baseball, None };
enum grade_acept { Yes, No };
 
struct students
{
system_names an;
class_level cl;
sport_teams st;
grade_acept ga;
};
 
int main()
{
students sport;
 int n;
 cout << " Kindly enter systen number which You want to communicate " << endl;
 cout << "0. ABC 1.SERVO 2.SIGCON 3.SENTINEL 4.CORRELATOR 5.SENTINEL"<<endl;
 cin >> n;
// cout << " User entered " << n << endl;    
sport.an = (system_names)n;
sport.cl = Senior;
sport.st = Football;
sport.ga = No;
 

  switch ( sport.an ) {
  case abc:
    cout << "USER SELECTED ABCCOM SYSTEM FOR COMMUNICATION \n";    
    break;
  case servo:         
    cout << "USER SELECTED SERVO SYSTEM FOR COMMUNICATION\n";    
    break;
  case sigcon:           
    cout << "USER SELECTED SIGCON SYSTEM FOR COMMUNICATION\n";    
    break;
  case correlator:        
    cout << "USER SELECTED CORRELATOR SYSTEM FOR COMMUNICATION\n";  
    break;
  case sentinel:        
    cout << "USER SELECTED SENTINEL SYSTEM FOR COMMUNICATION\n";  
    break;
  default:     
    break;
  }
 
return 0;
}
