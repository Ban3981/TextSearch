#include "Words.h"
#include <sstream>
#include <iostream>
#include <algorithm>


            Words::Words(const Sentences& sentence)
            {
                extractWords(sentence);
            }


            std::ostream& operator<<(std::ostream& output,const Words& other)
            {
                for(const auto& x:other.mapOfWords)
                {
                    output<<x.first<<' ';
                    for(const auto& y:x.second)
                        std::cout<<y<<' ';
                    std::cout<<std::endl;
                }
                return output;
            }


            void Words::extractWords(const Sentences& sentence) noexcept
            {

                for(unsigned int i=0;i<sentence.size();++i)
                {
                    std::string temp=sentence.getSentence(i);
                    char c=temp.back();
                    temp.pop_back();

                    std::stringstream interpunction;
                        interpunction<<c;
                    std::stringstream stream(std::move(temp));

                    putStringToMap(stream,i);
                    putStringToMap(interpunction,i);
                }
            }


            void Words::putStringToMap(std::stringstream& stream,unsigned int i) noexcept
            {
                while(stream)
                {
                    std::string current;
                    stream>>current;
                    if(stream)
                    {
                        auto result=mapOfWords.insert( std::pair<std::string,std::set<unsigned int>>({current, std::set<unsigned int>({i}) }));
                        if(!result.second)  //This word already exists in map,I'll add only sentence number for this word
                            result.first->second.insert(i);
                    }
                }

            }


            std::list<unsigned int> Words::findSentencesWhichContainAllTheWords(const std::vector<std::string>& strings) const noexcept
            {

                std::list<unsigned int> result;
                for(auto stringsIt=strings.cbegin();stringsIt!=strings.cend();++stringsIt)
                {
                    auto mapIt=mapOfWords.find(*stringsIt);

                    if(mapIt==mapOfWords.end()) //there is a word which doesn't exist in map
                    {
                        result.clear();
                        return result;
                    }
                    else
                    {
                        if(result.empty())
                            result.assign(mapIt->second.cbegin(),mapIt->second.cend());
                        else
                        {
                            std::list<unsigned int> temp;
                            temp.swap(result);
                            std::set_intersection(temp.cbegin(),temp.cend(),mapIt->second.cbegin(),mapIt->second.cend(),
                                                  std::back_insert_iterator<std::list<unsigned int>>(result));
                        }
                    }
                }

                result.unique();
                return result;
            }


            std::list<unsigned int> Words::findSentencesWhichContaninAtLeastOneOfTheWords(const std::vector<std::string>& strings) const noexcept
            {
                std::list<unsigned int> result;
                for(auto stringIt=strings.cbegin();stringIt!=strings.cend();++stringIt)
                {
                    auto mapIt=mapOfWords.find(*stringIt);
                    if(mapIt!=mapOfWords.end())
                        performUnion(result,mapIt);
                }

                result.unique();
                return result;
            }


            std::list<unsigned int> Words::findSentencesWhichDontContainAnyOfTheWords(const std::vector<std::string>& strings,int numberOfSentences) const noexcept
            {
                std::list<unsigned int> result(numberOfSentences);
                unsigned int counter=0;
                for(auto it=result.begin();it!=result.end();++it)
                    *it=counter++;

                std::list<unsigned int> sentencesWithSentStrings;
                for(auto stringIt=strings.cbegin();stringIt!=strings.cend();++stringIt)
                {
                    auto mapIt=mapOfWords.find(*stringIt);
                    if(mapIt!=mapOfWords.end())
                        performUnion(sentencesWithSentStrings,mapIt);

                }

                sentencesWithSentStrings.unique();
                std::list<unsigned int> temp;
                temp.swap(result);
                std::set_difference(temp.cbegin(),temp.cend(),
                               sentencesWithSentStrings.cbegin(),sentencesWithSentStrings.cend(),
                               std::back_insert_iterator<std::list<unsigned int>>(result));

                return result;
            }



            void Words::performUnion(std::list<unsigned int>& result,std::map<std::string,std::set<unsigned int>>::const_iterator& mapIt) const noexcept
            {
                if(result.empty())
                    result.assign(mapIt->second.cbegin(),mapIt->second.cend());
                else
                {
                    std::list<unsigned int> temp;
                    temp.swap(result);
                    std::set_union(temp.cbegin(),temp.cend(),
                                   mapIt->second.cbegin(),mapIt->second.cend(),
                                   std::back_insert_iterator<std::list<unsigned int>>(result));
                }
            }










