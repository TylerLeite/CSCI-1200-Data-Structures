#include "student.h"

void Student::PrepareToReceiveOffers(){
    return;
}

void Student::AddSchool(const std::string& school){
    std::list<std::string>::iterator school_it = pref_list.begin();
    for (; school_it != pref_list.end(); school_it++){
        if (*school_it == school){
            std::cerr << "WARNING: could not add " << school
                      << " into student preference list, this school is already in the list"
                      << std::endl;
            //exit(1);
            return;
        }
    }
    
    pref_list.insert(pref_list.end(), school);
}

bool Student::IsOfferTentativelyAccepted(const std::string& school){
  //pref list is ordered by descending preference
    std::list<std::string>::const_iterator school_it = pref_list.begin();
    for (; school_it != pref_list.end(); school_it++){
      //if student has recieved an offer and it is higher on the pref list,
      // decline the offer
        if (best_offer_so_far != "" && *school_it == best_offer_so_far){
            return false;
        } else if (*school_it == school){
          //accept the offer if it's on the pref list and above best_offer_so_far
            best_offer_so_far = school;
            return true;
        }
    }

    //school not on pref list
    return false;
}

void Student::PrintPreferenceList(std::ostream& out) const {
    out << name << " preference list:";
    
    std::list<std::string>::const_iterator school_it = pref_list.begin();
    int rank = 1;
    for (; school_it != pref_list.end(); school_it++){
      //assuming pref list is in order
        out << std::endl << std::setw(3) << rank << ". " << *school_it;
        rank++;
    }

    out << std::endl << std::endl;
    return;
}

void Student::PrintStudentDecision(std::ostream& out) const {
    if (best_offer_so_far == ""){
      //-> no offers were made by schools on the student's preference list
        out << name << " has not received an acceptable offer" << std::endl;
    } else {
        out << name << " will be attending " << best_offer_so_far << std::endl;
    }
}
