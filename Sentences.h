#pragma once
#include <string>
#include <vector>
#include <fstream>


            class Sentences
            {
                std::vector<std::string> vectorOfSentences;

            public:
                Sentences(const std::string&) noexcept(false);
                inline unsigned int size() const noexcept {return vectorOfSentences.size();}
                const std::string& getSentence(unsigned int) const noexcept(false);

            private:
                void extractSentences(std::ifstream&) noexcept;
            };
