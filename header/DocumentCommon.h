
#ifndef DOCUMENT_COMMON_OVERVIEW_H
#define DOCUMENT_COMMON_OVERVIEW_H

#include "CommonSample.h"

#include <Standard_WarningsDisable.hxx>
#include <QObject>
#include <QList>
#include <Standard_WarningsRestore.hxx>

#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>

class ApplicationCommonWindow;

//! Implements visualization of samples content
class DocumentCommon : public QObject
{
    Q_OBJECT
public:

    DocumentCommon(ApplicationCommonWindow*);
    ~DocumentCommon() { }

    const Handle(AIS_InteractiveContext)& getContext() { return myContext; }

    const Handle(V3d_Viewer)& getViewer() { return myViewer; }

    void setViewer(const Handle(V3d_Viewer)& theViewer) { myViewer = theViewer; }

    void SetObjects(const NCollection_Vector<Handle(AIS_InteractiveObject)>& theObjects,
        Standard_Boolean theDisplayShaded = Standard_False);
    void Clear();
    bool IsEmpty() const { return myContextIsEmpty; }

signals:
    void selectionChanged();
    void sendCloseDocument(DocumentCommon*);

private:
    Handle(V3d_Viewer) Viewer(const Standard_ExtString theName,
        const Standard_CString theDomain,
        const Standard_Real theViewSize,
        const V3d_TypeOfOrientation theViewProj,
        const Standard_Boolean theComputedMode,
        const Standard_Boolean theDefaultComputedMode);

private:
    Handle(V3d_Viewer)             myViewer;
    Handle(AIS_InteractiveContext) myContext;
    bool myContextIsEmpty;
};

#endif
