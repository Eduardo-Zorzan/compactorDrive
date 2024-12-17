#include "googleDrive.h"

namespace Drive {
    string get() {
        Response test = Get(Url("https://www.googleapis.com/drive/v3/about"));
        return test.text;
    }
}
