#pragma once
#include "Sentences.h"
#include <map>
#include <set>
#include <string>
#include <list>


            class Words
            {
                std::map<std::string,std::set<unsigned int>> mapOfWords;

            public:
                Words(const Sentences&);
                friend std::ostream& operator<<(std::ostream&,const Words&);
                std::list<unsigned int> findSentencesWhichContainAllTheWords(const std::vector<std::string>&) const noexcept;
                std::list<unsigned int> findSentencesWhichContaninAtLeastOneOfTheWords(const std::vector<std::string>&) const noexcept;
                std::list<unsigned int> findSentencesWhichDontContainAnyOfTheWords(const std::vector<std::string>&,int) const noexcept;

            private:
                void extractWords(const Sentences&) noexcept;
                void putStringToMap(std::stringstream&,unsigned int) noexcept;
                void performUnion(std::list<unsigned int>&,std::map<std::string,std::set<unsigned int>>::const_iterator&) const noexcept;
            };
