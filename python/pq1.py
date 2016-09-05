import sys
from PyQt import QtGui

app = QtGui.QApplication(sys.argv)
widget = QtGui.QWidget()
widget.resize(250,150)
widget.setWindowTitle('simple')
widget.show()
sys.exit(app.exec_())
