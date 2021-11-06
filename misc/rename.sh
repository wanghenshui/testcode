 for line in $(find . -name "*.py")\ndo \nmv $line ./py/\ndone
 for line in $(find . -name "*.hpp")\ndo \nmv $line ./cpp/\ndone
 for line in $(find . -name "*.hh")\ndo \nmv $line ./cpp/\ndone
 for line in $(find . -name "*.h")\ndo \nmv $line ./cpp/\ndone
 for line in $(find . -name "*.c")\ndo \nmv $line ./cpp/\ndone
 for line in $(find . -name "*.cc")\ndo \nmv $line ./cpp/\ndone
