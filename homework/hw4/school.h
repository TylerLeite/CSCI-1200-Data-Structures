#ifndef SCHOOL_H
#define SCHOOL_H

#include <iostream>
#include <iomanip>
#include <list>
#include <string>

class School {
    public:
        School(const std::string& name, int num_slots) :
            name(name), last_offer("none"), num_slots(num_slots)
        {
            pref_list.insert(pref_list.end(), ""); //mark the end of the list
        }

        void PrepareToMakeOffers();

        void AddStudent(const std::string& student);

        std::string MakeNextOffer();

        void StudentDeclinesTentativeAcceptance(const std::string& student);

        void PrintPreferenceList(std::ostream& out) const;
        void PrintSchoolEnrollment(std::ostream& out);

     // One-line member functions
        void StudentTentativelyAcceptsOffer(const std::string& student);
       
        int NumAcceptedStudents(){return tentative_enrollment.size();}
        int MaxAcceptedStudents(){return num_slots;}

        std::string GetName() const {return name;}
        std::list<std::string>* GetPreferenceList(){return &pref_list;}
        
    protected:
        const std::string name;
        std::string last_offer;
        int num_slots;
        std::list<std::string> pref_list;
        std::list<std::string> tentative_enrollment;
};

#endif
