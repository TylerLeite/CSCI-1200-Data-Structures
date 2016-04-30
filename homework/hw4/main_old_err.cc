#include <iostream>
#include <fstream>
#include <list>
#include <cassert>
#include <cstdlib>

#include "school.h"
#include "student.h"


// ==========================================================================================
// IMPORTANT: Carefully read this file, but do not make any changes to
//            the code, except to fill in code where indicated, and 
//            (if necessary) add appropriate error messages.
// ==========================================================================================

bool alpha_by_school_name(const School& lhs, const School& rhs){
    return lhs.GetName() < rhs.GetName();
}
bool alpha_by_student_name(const Student& lhs, const Student& rhs){
    return lhs.GetName() < rhs.GetName();
}

// read the data for a school & add to the schools list
void AddSchool(std::istream &istr, std::list<School> &schools) {
  std::string school_name, student_name;
  int num_slots, num_prefs;
  istr >> school_name >> num_slots >> num_prefs;

  // create the school
  School s(school_name, num_slots);
  for (int i = 0; i < num_prefs; i++) {
    istr >> student_name;
    // add the students in the order listed
    s.AddStudent(student_name);
  }

/// Error checking
    std::list<School>::iterator school_it = schools.begin();
    for (; school_it != schools.end(); school_it++){
        if (school_it->GetName() == school_name){
            std::cerr << "Error, trying to create already existing school \""
                      << school_name << "\"" << std::endl;
            //exit(1);
            return;
        }
    }
//end error checking

  // add to the schools list
  schools.push_back(s);
}

// read the data for a student & add to the students list
void AddStudent(std::istream &istr, std::list<Student> &students) {
  std::string student_name, school_name;
  int num_prefs;
  istr >> student_name >> num_prefs;

  // Create the student
  Student s(student_name);
  for (int i = 0; i < num_prefs; i++) {
    istr >> school_name;
    // add the schools in the order listed
    s.AddSchool(school_name);
  }

/// Error checking
    std::list<Student>::iterator student_it = students.begin();
    for (; student_it != students.end(); student_it++){
        if (student_it->GetName() == student_name){
            std::cerr << "Error, trying to create already existing student \""
                      << student_name << "\"" << std::endl;
            //exit(1);
            return;
        }
    }
//end error checking
  
  // add to the students list
  students.push_back(s);
}

// ==========================================================================================

// read data and add a student into a school's preference list
void InsertStudentIntoSchoolPreferenceList(std::istream &istr, std::list<School> &schools) {
  std::string new_student_name, school_name, insert_before_student_name;
  istr >> school_name >> new_student_name >> insert_before_student_name;

/// FILL IN THIS FUNCTION
    std::list<School>::iterator school_it = schools.begin();
    for (; school_it != schools.end(); school_it++){
        if (school_it->GetName() == school_name){
          //stop when school is found
            break;
        }
    }

    if (school_it == schools.end()){
            //error, school wasn't found
            std::cerr << "Error, trying to insert new student \"" << new_student_name
                      << "\" into a the preference list of a nonexistant school \"" 
                      << insert_before_student_name << std::endl;
            //exit(1);
            return;
    } else {
        std::list<std::string>* pref_list = school_it->GetPreferenceList();
        std::list<std::string>::iterator student_it = pref_list->begin();
        std::list<std::string>::iterator temp = pref_list->end();;
        for (; student_it != pref_list->end(); student_it++){
            if (*student_it == new_student_name){
                std::cerr << "Error, trying to add a student \"" << new_student_name 
                          << " to the preference list of school \"" << school_name
                          << "\", but that student is already on the list"
                          << std::endl;
            }
            
            if (*student_it == insert_before_student_name){
              //remember when the iterator is at the name to be inserted before,
              //but keep going to check for duplicates
                temp = student_it;
            }
        }
      //insert new student in the proper location
        if (temp == pref_list->end()){
            std::cerr << "Error, trying to insert new student \"" << new_student_name
                      << "\" before nonexistant student \"" << insert_before_student_name 
                      << "in the preference list for school \"" << school_name << "\"" 
                      << std::endl;
            //exit(1);
            return;
        } else {
            pref_list->insert(temp, new_student_name);
            return;
        }
    }
}

// read data and remove a particular school from a student's preference list
void RemoveSchoolFromStudentPreferenceList(std::istream &istr, std::list<Student> &students) {
  std::string school_name, student_name;
  istr >> student_name >> school_name;

/// FILL IN THIS FUNCTION
    std::list<Student>::iterator student_it = students.begin();
    for (; student_it != students.end(); student_it++){
        if (student_it->GetName() == student_name){
          //stop when the student is found
            break;
        }
    }

    if (student_it == students.end()){
        //error, student not in list
        std::cerr << "Error, trying to remove school \"" << school_name 
                  << " from preference list of nonexistant student \"" 
                  << student_name << std::endl;
        //exit(1);
    } else {
        std::list<std::string>* pref_list = student_it->GetPreferenceList();
        std::list<std::string>::iterator school_it = pref_list->begin();
        for (; school_it != pref_list->end(); school_it++){
            if (*school_it == school_name){
              //find the student and promptly erase the entry
                pref_list->erase(school_it);
                return;
            }
        }
    }

    //only runs if school not in student's pref list
    std::cerr << "Error, trying to remove school \"" << school_name 
              << " from student \"" << student_name 
              << "'s preference list, but that school is not on it." 
              << std::endl;
    
    //exit(1);
}

// ==========================================================================================
// The Gale-Shapley algorithm to solve the Stable Marriage Problem

void PerformMatching(std::list<School> &schools, std::list<Student> &students, std::ofstream &ostr) {
  // Perform any initialization necessary for the school and student objects
  for (std::list<School>::iterator itr = schools.begin(); itr != schools.end(); itr++) {
    itr->PrepareToMakeOffers(); 
  }
  for (std::list<Student>::iterator itr = students.begin(); itr != students.end(); itr++) {
    itr->PrepareToReceiveOffers();
  }

  // Iterate until the matching is stable (no changes)
  int which_iteration = 1;
  while(1) {
    ostr << "---- ROUND " << which_iteration << " ----" << std::endl;
    which_iteration++;
    // keep track of the offers made during this round
    int offers_made = 0;
    
    for (std::list<School>::iterator school_itr = schools.begin(); school_itr != schools.end(); school_itr++) {
      if (school_itr->NumAcceptedStudents() == school_itr->MaxAcceptedStudents()) continue;

      // Each school that has open slots, makes an offer to the next student on their preference list
      std::string student = school_itr->MakeNextOffer();
      // an empty string indicates that this school has reached the end of its preference list
      if (student == "") continue;
      ostr << school_itr->GetName() << " makes an offer to " << student << std::endl;
      offers_made++;

      for (std::list<Student>::iterator student_itr = students.begin(); student_itr != students.end(); student_itr++) {
	// loop through the students to find the student object with that name
	if (student_itr->GetName() == student) {
	  
	  // check to see if that student has tentatively accepted an offer from another school
	  std::string current_choice = "";
	  if (student_itr->HasOffer()) { 
	    current_choice = student_itr->GetBestOffer(); 
	  }
	  // make the offer to the student, returns true if the school is on the student's 
	  // preference list and is better than the students current offer (if any)
	  bool tentative_acceptance = student_itr->IsOfferTentativelyAccepted(school_itr->GetName());
	  if (!tentative_acceptance) {
	    ostr << "  " << student << " declines offer from " << school_itr->GetName() << std::endl;
	  } else {
	    if (current_choice != "") {
	      // if the student had a prior acceptance, decline the earlier offer
	      for (std::list<School>::iterator school2_itr = schools.begin(); school2_itr != schools.end(); school2_itr++) {
		if (school2_itr->GetName() == current_choice) {
		  ostr << "  " << student << " withdraws tentative acceptance of offer from " << current_choice << std::endl;		
		  school2_itr->StudentDeclinesTentativeAcceptance(student);
		}
	      }	    
	    }
	    // student tentatively accepts the offer from the (new) school
	    school_itr->StudentTentativelyAcceptsOffer(student);
	    ostr << "  " << student << " tentatively accepts offer from " << school_itr->GetName() << std::endl;
	  }
	}
      }
    }
    if (offers_made == 0) {
      ostr << "no offers_made this round" << std::endl << std::endl;
      break;
    }
  }
}

// ==========================================================================================
// PRINTING

// Print the ranking of students by a particular school
void PrintSchoolPreferenceList(std::istream &istr, const std::list<School> &schools, std::ostream &ostr) {
  std::string school_name;
  istr >> school_name;

/// FILL IN THIS FUNCTION
    std::list<School>::const_iterator school_it = schools.begin();
    for (; school_it != schools.end(); school_it++){
        if (school_it->GetName() == school_name){
            school_it->PrintPreferenceList(ostr);
            return;
        }
    }

    std::cerr << "Error, trying to print preference list of nonexistant school \""
              << school_name << "\"" << std::endl;
    //exit(1);
}

// Print a ranking of schools by a particular student
void PrintStudentPreferenceList(std::istream &istr, const std::list<Student> &students, std::ostream &ostr) {
  std::string student_name;
  istr >> student_name;

/// FILL IN THIS FUNCTION
    std::list<Student>::const_iterator student_it = students.begin();
    for (; student_it != students.end(); student_it++){
        if (student_it->GetName() == student_name){
            student_it->PrintPreferenceList(ostr);
            return;
        }
    }

    //error, student not found
    std::cerr << "Error, trying to print preference list of nonexistant student \""
              << student_name << "\"" << std::endl;
    //exit(1);
}

// Print the list of all schools (sorted alphabetically) and the students enrolled (also alphabetically)
void PrintSchoolEnrollments(std::list<School> &schools, std::ofstream &ostr) {
  schools.sort(alpha_by_school_name);
  for (std::list<School>::iterator itr = schools.begin(); itr != schools.end(); itr++) {
    itr->PrintSchoolEnrollment(ostr);
  }
  ostr << std::endl;
}

// Print a list of the students (sorted alphabetically) and the school they will attend (if any)
void PrintStudentDecisions(std::list<Student> &students, std::ofstream &ostr) {
  students.sort(alpha_by_student_name);
  for (std::list<Student>::const_iterator itr = students.begin(); itr != students.end(); itr++) {
    itr->PrintStudentDecision(ostr);
  }
  ostr << std::endl;
}

// ==========================================================================================

int main(int argc, char* argv[]) {

  // process command line arguments
  if (argc != 3) {
    std::cerr << "ERROR: incorrect number of command line arguments" << std::endl;
    std::cerr << "USAGE:   " << argv[0] << " <input_file> <output_file>" << std::endl;
    exit(1);
  }
  // open the input file for parsing
  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "ERROR: could not open input file " << argv[1] << std::endl;
    exit(1);
  }
  // open the output file
  std::ofstream ostr(argv[2]);
  if (!ostr) {
    std::cerr << "ERROR: could not open output file " << argv[2] << std::endl;
    exit(1);
  }

  // lists to store school and student objects
  std::list<School> schools;
  std::list<Student> students;

  // parse the file
  std::string keyword;
  while(istr >> keyword) {
    if (keyword == std::string("add_school")) {
      AddSchool(istr,schools);
    } else if (keyword == std::string("insert_student_into_school_preference_list")) {
      InsertStudentIntoSchoolPreferenceList(istr,schools);
    } else if (keyword == std::string("print_school_preferences")) {
      PrintSchoolPreferenceList(istr,schools,ostr);
    }

    else if (keyword == std::string("add_student")) { 
      AddStudent(istr,students);
    } else if (keyword == std::string("remove_school_from_student_preference_list")) { 
      RemoveSchoolFromStudentPreferenceList(istr,students);
    } else if (keyword == std::string("print_student_preferences")) {
      PrintStudentPreferenceList(istr,students,ostr);
    } 

    else if (keyword == std::string("perform_matching")) {
      PerformMatching(schools,students,ostr);
    } else if (keyword == std::string("print_school_enrollments")) {
      PrintSchoolEnrollments(schools,ostr);
    } else if (keyword == std::string("print_student_decisions")) {
      PrintStudentDecisions(students,ostr);
    } else {
      std::cerr << "unknown keyword in input file: " << keyword << std::endl;
      exit(1);
    }
  }
}

// ==========================================================================================
