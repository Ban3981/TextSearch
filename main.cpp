#include "ExecuteSearch.h"
#include <iostream>

            int main(int argc,const char** argv)
            {
              try
              {
                  ExecuteSearch(argc,argv);
              }
              catch(const std::exception& ex)
              {
                  std::cout<<ex.what();
              }

              return 0;

            }
