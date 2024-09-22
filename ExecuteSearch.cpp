#include "ExecuteSearch.h"
#include "ConvertUserInput.h"
#include "Sentences.h"
#include "Words.h"
#include <fstream>
#include <iostream>
#include <iomanip>


            void ExecuteSearch::print(const std::list<unsigned int>& indexes,const Sentences& sentences) const noexcept
            {
                std::cout<<std::right;
                for(auto it=indexes.cbegin();it!=indexes.cend();++it)
                    std::cout<<std::setw(4)<<(*it)+1<<" - "<<sentences.getSentence(*it)<<std::endl;
            }


            ExecuteSearch::ExecuteSearch(int argc,const char** argv) noexcept(false)
            {
                if(argc<2)
                    throw std::invalid_argument("Missing file path!");
                Sentences varSentences(argv[1]);
                Words varWords(varSentences);
                std::vector<std::vector<std::string>> userWords = ConvertUserInput::convert(argc-2,argv+2);  //avoid first argument
                //(which is program path) and second(that is a adress of file which we will analyse)

                std::list<unsigned int> result;
                std::cout<<"<<< << REPORT >> >>>\n\n";

                std::cout<<"Words with '+' : ";
                for(const auto& x:userWords[0])
                    std::cout<<x<<"  ";
                std::cout<<std::endl;

                std::cout<<"Words with '-': ";
                for(const auto& x:userWords[1])
                    std::cout<<x<<"  ";
                std::cout<<std::endl;

                std::cout<<std::endl;

                std::cout<<"Sentences which contain all the words with prefix '+' :"<<std::endl;
                result=varWords.findSentencesWhichContainAllTheWords(userWords[0]);
                print(result,varSentences);
                std::cout<<std::endl;

                std::cout<<"Sentences which contain at least one of the words with prefix '+' :"<<std::endl;
                result=varWords.findSentencesWhichContaninAtLeastOneOfTheWords(userWords[0]);
                print(result,varSentences);
                std::cout<<std::endl;

                std::cout<<"Sentences which don't contain any of the words with prefix '-' :"<<std::endl;
                result=varWords.findSentencesWhichDontContainAnyOfTheWords(userWords[1],varSentences.size());
                print(result,varSentences);
                std::cout<<std::endl;

                std::getchar();
                std::getchar();
            }
