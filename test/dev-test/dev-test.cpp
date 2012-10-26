#include <dsb/dsb.h>
#include <dsb/nid.h>
#include <dsb/singletonns.h>
#include <iostream>
#include <memory>

using namespace std;

int main() {
  cout << "Hello World.\n";
  
  unique_ptr<dsb::DSB> mydsb(new dsb::DSB("test"));
  mydsb->Initialise();
  
  unique_ptr<dsb::SingletonNS> myns(new dsb::SingletonNS(dsb::NID(5)));
  cout << "NS: " << myns->Get(0) << endl;
}
