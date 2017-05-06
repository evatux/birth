// ver. 0.1.2

#include <QApplication>

#include "birth.h"
#include "editorform.h"

int main(int argc, char *argv[])
{
    QApplication::setDesktopSettingsAware(false);
    QApplication app(argc, argv);
    app.setApplicationName("Birth");
    app.setApplicationVersion(birth_version);
    app.setOrganizationName("HNTeam");
    app.setWindowIcon(QIcon(":/cakes/cake01.png"));

    if (argc == 1) {
        EditorForm editor;
        editor.loadSettings();
        editor.show();
        return app.exec();
    }

    if (argc==2 && (!strcmp(argv[1],"-c") || !strcmp(argv[1],"--check"))) return run_check();
    if (argc==2 && (!strcmp(argv[1],"-v") || !strcmp(argv[1],"--version"))) return run_version();

    return run_help();
}
