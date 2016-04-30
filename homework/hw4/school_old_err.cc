#include "school.h"

void School::PrepareToMakeOffers(){
}

void School::AddStudent(const std::string& student){
    std::list<std::string>::iterator student_it = pref_list.begin();
    for (; student_it != pref_list.end(); student_it++){
        if (*student_it == student){
            std::cerr << "Error, student \"" << student 
                      << "\" is already on the preference list of school \""
                      << name << std::endl;
            //exit(1);
            return;
        }
    }
    student_it--;
  //place the student before the empty string
    pref_list.insert(student_it, student);    
}

std::string School::MakeNextOffer(){
    if (last_offer == "none"){
        last_offer = *(pref_list.begin());
        return last_offer;
    }
    
    std::list<std::string>::iterator student_it = pref_list.begin();
    for (; student_it != pref_list.end(); student_it++){
        if (*student_it == ""){
          //it's the end of the line!
            last_offer = "";
            return "";
        } else if (*student_it == last_offer){
          //update last offer, return the next one
            student_it++;
            last_offer = *student_it;
            return last_offer;
        }
    }

    return "";
}

void School::StudentTentativelyAcceptsOffer(const std::string& student){
    tentative_enrollment.insert(tentative_enrollment.end(), student);
}

void School::StudentDeclinesTentativeAcceptance(const std::string& student){
    std::list<std::string>::iterator student_it = tentative_enrollment.begin();
    for (; student_it != tentative_enrollment.end(); student_it++){
        if (*student_it == student){
          //find student and erase the entry, return to not throw error and to
          //not keep iterating with a broken iterator
            tentative_enrollment.erase(student_it);
            return;
        }
    }

    //error, student never accepted -> cant decline
    std::cerr << "Error, attempting to process declination of student \'" 
              << student <<"\" who never accepted an offer from school \""
              << name << "\"" << std::endl;
    //exit(1);
}

void School::PrintPreferenceList(std::ostream& out) const {
    out << name << " preference list:";

    std::list<std::string>::const_iterator student_it = pref_list.begin();
    int rank = 1;
    for (; student_it != pref_list.end(); student_it++){
      //assuming preference lists are already ordered
        if (*student_it == "") continue;
        out << std::endl << std::setw(3) << rank << ". " << *student_it;
        rank++;
    }

    out << std::endl << std::endl;
    return;
}

void School::PrintSchoolEnrollment(std::ostream& out){
  //sort alphabetically
    tentative_enrollment.sort();

    out << "student(s) who will be attending " << name << ":";

    std::list<std::string>::const_iterator student_it = tentative_enrollment.begin();
    for (; student_it != tentative_enrollment.end(); student_it++){
        out << std::endl << "  " << *student_it;
    }

    int spots_left = num_slots - tentative_enrollment.size();
    if (spots_left > 0){
      //if there are still spots open to be filled
        out << std::endl << "  [" << spots_left << " remaining slot(s) in enrollment]"; 
    }

    out << std::endl;
}
