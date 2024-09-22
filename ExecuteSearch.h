#pragma once
#include "Sentences.h"
#include <list>

            class ExecuteSearch
            {
                public:
                    ExecuteSearch(int,const char**) noexcept(false);
                private:
                    void print(const std::list<unsigned int>&,const Sentences&) const noexcept;
            };
