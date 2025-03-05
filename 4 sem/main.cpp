#include "1.h"

int main(void) {
    vector<MyClass *> v; CintN1 ob;
    MyClass::Input("data.txt", v);

    cout << "File input test" << endl << endl;

    for (size_t i = 0; i < v.size(); ++i) v[i]->Show();

    cout << endl << "Destructor test" << endl;

    for (size_t i = 0; i < v.size(); ++i) delete v[i];

    cout << endl << "Method inheritance test" << endl;

    for (size_t i = 0; i < N; ++i) ob[i] = N - i;
    ob.Show();

    return 0;
}
