#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <iomanip>
#include <list>
#include <string>

class Student {
    public:
        Student(std::string name) : 
            name(name), best_offer_so_far("")
        {}

        void AddSchool(const std::string& school);

        void PrepareToReceiveOffers();
        
        bool IsOfferTentativelyAccepted(const std::string& school);

        void PrintPreferenceList(std::ostream& out) const;
        void PrintStudentDecision(std::ostream& out) const;

     // One-line member functions
        bool HasOffer(){return best_offer_so_far != "";}
        std::string GetBestOffer(){return best_offer_so_far;}

        std::string GetName() const {return name;}
        std::list<std::string>* GetPreferenceList(){return &pref_list;}
        
    protected:
        const std::string name;
        std::string best_offer_so_far;
        std::list<std::string> pref_list;
};

#endif
