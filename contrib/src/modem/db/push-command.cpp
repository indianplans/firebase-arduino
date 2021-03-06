#include "modem/db/commands.h"
#include "modem/json_util.h"

namespace firebase {
namespace modem {

bool PushCommand::execute(const String& command,
                         InputStream* in, OutputStream* out) {
  if (in == nullptr || out == nullptr) {
    return false;
  }

  if (command != "PUSH") {
    return false;
  }

  String path =  in->readStringUntil(' ');
  String data = in->readLine();

  fbase().pushString(path, data);

  if (fbase().error().length() != 0) {
    out->print("-FAIL ");
    out->println(fbase().error().c_str());
    return false;
  } else {
    out->println("+OK");
    return true;
  }
}

}  // modem
}  // firebase
