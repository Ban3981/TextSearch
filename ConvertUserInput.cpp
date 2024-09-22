#include "ConvertUserInput.h"
#include <fstream>
#include <stdexcept>


            std::vector<std::vector<std::string>> ConvertUserInput::convert(int size,const char** strings) noexcept(false)
            {
                std::vector<std::vector<std::string>> matrixOfStrings(size);
                for(int i=0;i<size;++i)
                {
                    std::string temp(strings[i]);
                    std::string result(++temp.begin(),temp.end());
                    if(temp.front()=='+')
                        matrixOfStrings[0].push_back(result);
                    else
                        matrixOfStrings[1].push_back(result);
                }

                return matrixOfStrings;
            }

