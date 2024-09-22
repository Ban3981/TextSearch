#include "Sentences.h"



            Sentences::Sentences(const std::string& sourceName) noexcept(false)
            {
                std::ifstream source(sourceName);
                if(source)
                {
                    extractSentences(source);
                    source.close();
                }
                else
                {
                    source.close();
                    throw std::invalid_argument("Invalid source file!");
                }
            }


            const std::string& Sentences::getSentence(unsigned int index) const noexcept(false)
            {
                if(index>vectorOfSentences.size()-1)
                    throw std::out_of_range("Wrong index value!");
                return vectorOfSentences[index];
            }


            void Sentences::extractSentences(std::ifstream& file) noexcept
            {
                int currentSize=1;
                vectorOfSentences.resize(currentSize);

                char c;
                for(c=file.get();file;c=file.get())
                {
                    if(file)
                    {
                        if(c!='\n' || c=='\t')
                            vectorOfSentences[currentSize-1].push_back(c);

                        if(c=='.' || c=='?' || c=='!')
                        {
                            ++currentSize;
                            vectorOfSentences.resize(currentSize);
                        }
                    }
                }

                vectorOfSentences.pop_back();
            }
