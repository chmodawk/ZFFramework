/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFUIView.h
 * @brief base class of all UI views
 */

#ifndef _ZFI_ZFUIView_h_
#define _ZFI_ZFUIView_h_

#include "ZFUIViewType.h"
#include "ZFUIMouseEvent.h"
#include "ZFUIKeyEvent.h"
#include "ZFUIWheelEvent.h"

ZF_NAMESPACE_GLOBAL_BEGIN

/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFUIView_internalImplView zfText("internalImplView")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFUIView_internalBackgroundView zfText("internalBackgroundView")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFUIView_internalForegroundView zfText("internalForegroundView")

/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFUIView_child zfText("child")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFUIView_layoutParam zfText("layoutParam")

// ============================================================
zfclassFwd ZFUIView;
/**
 * @brief see #ZFUIView::nativeImplViewSet
 */
typedef void (*ZFUIViewNativeImplViewDeleteCallback)(ZF_IN ZFUIView *view, ZF_IN void *nativeImplView);

// ============================================================
// ZFUIView
zfclassFwd _ZFP_ZFUIViewPrivate;
/**
 * @brief base class of all UI views
 *
 * ZFUIView has these layer of views:
 * -  internal impl view:
 *   for subclass to add views behind native impl view
 * -  internal native view:
 *   for impl to achieve different functions, internal use only
 * -  internal background view:
 *   for subclass to add background views
 * -  normal view:
 *   common children views
 * -  internal foreground view:
 *   for subclass to add foreground views
 *
 * all view layer is implemented internally by simple view management\n
 * \n
 * ZFUIView is serializable and styleable, see #ZFSerializable and #ZFStyleable for more info,
 * all property and normal children views would be serialized and styled automatically,
 * but internal views must be processed by subclass manually\n
 * \n
 * serializable data:
 * @code
 *   <ViewClass>
 *       // optional, see #internalViewAutoSerializeTagAdd
 *       <ChildClass category="internalImplView" >
 *       // optional, see #internalViewAutoSerializeTagAdd
 *       <ChildClass category="internalBackgroundView" >
 *       </ChildClass>
 *       // optional, see #internalViewAutoSerializeTagAdd
 *       <ChildClass category="internalForegroundView" >
 *       </ChildClass>
 *
 *       <ChildClass category="child" >
 *           // layout param for parent, optional
 *           <LayoutParamClass category="layoutParam" ... />
 *       </ChildClass>
 *       ... // all children
 *   </ViewClass>
 * @endcode
 * by default, internal views won't be serialized automatically,
 * except matches these condition:
 * -  have the viewId of your internal view been set
 * -  have the same viewId registered by #internalViewAutoSerializeTagAdd
 *
 * \n
 * ADVANCED:\n
 * we allow add native view to ZFUIView environment,
 * for how to, refer to #ZFUINativeViewWrapper\n
 * we also allow add ZFUIView to native view,
 * for how to, refer to #ZFUISysWindow::nativeWindowEmbed
 */
zfclass ZF_ENV_EXPORT ZFUIView : zfextends ZFStyleableObject
{
    ZFOBJECT_DECLARE(ZFUIView, ZFStyleableObject)
    ZFSTYLE_DEFAULT_DECLARE(ZFUIView)

public:
    // ============================================================
    // events
    /**
     * @brief see #ZFObject::observerNotify
     *
     * called when child added or removed or order changed,
     * may be normal child or internal child
     */
    ZFOBSERVER_EVENT(ViewChildOnChange)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * called when child added to this view,
     * param0 is the child,
     * param1 is #ZFUIViewChildLayer
     */
    ZFOBSERVER_EVENT(ViewChildOnAdd)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * called when child removed from this view,
     * param0 is the child,
     * param1 is #ZFUIViewChildLayer
     */
    ZFOBSERVER_EVENT(ViewChildOnRemove)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * called when this view added to parent,
     * param0 is the parent added to
     */
    ZFOBSERVER_EVENT(ViewOnAddToParent)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * param0 is the parent removed from
     */
    ZFOBSERVER_EVENT(ViewOnRemoveFromParent)
    /**
     * @brief see #ZFObject::observerNotify
     */
    ZFOBSERVER_EVENT(ViewScaleOnChange)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * called when view's focus state changed, both obtain or resign
     */
    ZFOBSERVER_EVENT(ViewFocusOnChange)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * param0 is the #ZFUIEvent\n
     * you may resolve the event by #ZFEvent::eventResolvedSet
     * to prevent the event from being sent to its original receiver
     */
    ZFOBSERVER_EVENT(ViewOnEventFilter)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * param0 is the #ZFUIEvent
     */
    ZFOBSERVER_EVENT(ViewOnEvent)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * param0 is the view that caused this layout request\n
     * called when this view or any of children called #layoutRequest manually
     */
    ZFOBSERVER_EVENT(ViewLayoutOnLayoutRequest)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * param0 is a #ZFUIViewMeasureResult,
     * you may change the measured size to override the measure result
     */
    ZFOBSERVER_EVENT(ViewLayoutOnMeasureFinish)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * #layoutedFrame would be updated before this method,
     * you may safely modify children's #layoutParam during this method\n
     * note, you must not modify self's #layoutParam during the whole layout step
     */
    ZFOBSERVER_EVENT(ViewLayoutOnLayoutPrepare)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * called to do actual layout steps
     */
    ZFOBSERVER_EVENT(ViewLayoutOnLayout)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * called when layout finished,
     * typically you should not modify #layoutParam during this event
     */
    ZFOBSERVER_EVENT(ViewLayoutOnLayoutFinish)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * see #viewPropertyUpdateRequest
     */
    ZFOBSERVER_EVENT(ViewPropertyOnUpdate)

    // ============================================================
    // serialize
public:
    /**
     * @brief store ref layout param for this view
     *
     * typically for impl views,
     * if set, while serializing this view's layout param,
     * the ref one would be used as reference object to filter out contents that didn't change
     * (see #ZFSerializable::serializeToData)\n
     * by default, all impl child add methods (#internalBackgroundViewAdd series)
     * would call this method automatically
     */
    virtual void serializableRefLayoutParamSet(ZF_IN ZFUIViewLayoutParam *serializableRefLayoutParam);
    /** @brief see #serializableRefLayoutParamSet */
    virtual ZFUIViewLayoutParam *serializableRefLayoutParam(void);
protected:
    zfoverride
    virtual zfbool serializableOnSerializeFromData(ZF_IN const ZFSerializableData &serializableData,
                                                   ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                                   ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull);
    zfoverride
    virtual zfbool serializableOnSerializeToData(ZF_IN_OUT ZFSerializableData &serializableData,
                                                 ZF_IN ZFSerializable *referencedOwnerOrNull,
                                                 ZF_OUT_OPT zfstring *outErrorHint = zfnull);
    /**
     * @brief by default, #ZFUIView would serialize all normal child views,
     *   for some adapter view it may be not necessary,
     *   you may override this method to disable the auto serialization of child views
     */
    virtual zfbool serializableOnCheckNeedSerializeChildren(void);

public:
    // ============================================================
    // properties
    /**
     * @brief class name of a ZFUIView class,
     *   if set, all children would be managed by the delegate view
     *
     * if set, an instance of the class would be created and saved as
     * this view's delegate,
     * after that, all children would be managed by the delegate
     * (a complete list of functions affected by delegate would be listed below)\n
     * note: changing this property would cause all children been moved\n
     * \n
     * here's a list of functions that would be affected by delegate view:
     * -  #ZFUIView::childFindById
     * -  #ZFUIView::childAdd
     * -  #ZFUIView::childRemove
     * -  #ZFUIView::childRemoveAtIndex
     * -  #ZFUIView::childRemoveAll
     * -  #ZFUIView::childMove
     * -  #ZFUIView::childReplaceAtIndex
     * -  #ZFUIView::childCount
     * -  #ZFUIView::childAtIndex
     * -  #ZFUIView::childFind
     * -  #ZFUIView::childArray
     * -  #ZFUIView::childRawArray
     * -  #ZFUIView::layoutOnMeasure
     * -  #ZFUIView::layoutOnMeasureFinish
     * -  #ZFUIView::layoutOnLayoutPrepare
     * -  #ZFUIView::layoutOnLayout
     * -  #ZFUIView::layoutOnLayoutFinish
     */
    ZFPROPERTY_ASSIGN(zfstring, viewDelegateClass)
    ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(zfstring, viewDelegateClass);
    /**
     * @brief used to identify a view, empty by default
     *
     * this is useful when you want to find a view from a complicated view tree,
     * see #ZFUIView::childFindById
     * @note it's OK that two view have same view id,
     *   however it's recommended to make it unique
     */
    ZFPROPERTY_ASSIGN(zfstring, viewId)

    /**
     * @brief visible or not, zftrue by default
     */
    ZFPROPERTY_ASSIGN_WITH_INIT(zfbool, viewVisible,
                                ZFPropertyInitValue(zftrue))
    ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(zfbool, viewVisible);

    /**
     * @brief view's alpha, 1 by default
     */
    ZFPROPERTY_ASSIGN_WITH_INIT(zffloat, viewAlpha,
                                ZFPropertyInitValue(1))
    ZFPROPERTY_CUSTOM_ON_VERIFY_DECLARE(zffloat, viewAlpha)
    {
        propertyValue = zfmApplyRange<zffloat>(propertyValue, 0, 1);
    }
    ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(zffloat, viewAlpha);

    /**
     * @brief whether the view should receive user interaction
     *   (doesn't affect children, see #viewUIEnableTree)
     */
    ZFPROPERTY_ASSIGN_WITH_INIT(zfbool, viewUIEnable,
                                ZFPropertyInitValue(zftrue))
    ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(zfbool, viewUIEnable);

    /**
     * @brief whether the view as well as all its children should receive user interaction,
     *   see #viewUIEnable
     */
    ZFPROPERTY_ASSIGN_WITH_INIT(zfbool, viewUIEnableTree,
                                ZFPropertyInitValue(zftrue))
    ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(zfbool, viewUIEnableTree);

    /**
     * @brief whether enable mouse hover event, see #ZFUIView::viewEventOnMouseEvent, false by default
     */
    ZFPROPERTY_ASSIGN(zfbool, viewMouseHoverEventEnable)
    ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(zfbool, viewMouseHoverEventEnable);

    /**
     * @brief whether the view can be focused, false by default
     */
    ZFPROPERTY_ASSIGN(zfbool, viewFocusable)
    ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(zfbool, viewFocusable);
    /**
     * @brief whether try to obtain focus when clicked down, true by default
     */
    ZFPROPERTY_ASSIGN_WITH_INIT(zfbool, viewFocusObtainWhenClick,
                                ZFPropertyInitValue(zftrue))

    /**
     * @brief prefered size, #ZFUISizeInvalid by default
     *
     * if no actual rule to measure the view,
     * the prefered size would be used to measure the view,
     * if prefered size not set, size hint would be used
     */
    ZFPROPERTY_ASSIGN_WITH_INIT(ZFUISize, viewSizePrefered, ZFPropertyInitValue(ZFUISizeInvalid()))
    ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(ZFUISize, viewSizePrefered);
    /**
     * @brief min size, #ZFUISizeZero by default
     */
    ZFPROPERTY_ASSIGN(ZFUISize, viewSizeMin)
    ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(ZFUISize, viewSizeMin);
    /**
     * @brief max size, negative value means not set, #ZFUISizeInvalid by default
     */
    ZFPROPERTY_ASSIGN_WITH_INIT(ZFUISize, viewSizeMax,
                                ZFPropertyInitValue(ZFUISizeInvalid()))
    ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(ZFUISize, viewSizeMax);

    /**
     * @brief background color, #ZFUIColorTransparent by default
     */
    ZFPROPERTY_ASSIGN_WITH_INIT(ZFUIColor, viewBackgroundColor,
                                ZFPropertyInitValue(ZFUIColorTransparent()))
    ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(ZFUIColor, viewBackgroundColor);

    // ============================================================
    // init and dealloc
protected:
    zfoverride
    virtual void objectOnInit(void);
    zfoverride
    virtual void objectOnDealloc(void);
    zfoverride
    virtual void objectOnInitFinish(void);
    zfoverride
    virtual void objectOnDeallocPrepare(void);

public:
    zfoverride
    virtual zfidentity objectHash(void);
    zfoverride
    virtual ZFCompareResult objectCompare(ZF_IN ZFObject *anotherObj);

public:
    zfoverride
    virtual void objectInfoT(ZF_IN_OUT zfstring &ret);
protected:
    zfoverride
    virtual void objectInfoOnAppend(ZF_IN_OUT zfstring &ret);

protected:
    zfoverride
    virtual void objectCachedOnChange(void);

    // ============================================================
public:
    zffinal void _ZFP_ZFUIView_notifyLayoutNativeImplView(ZF_OUT ZFUIRect &result);
    /**
     * @brief native implementation view
     *
     * first child of #nativeView, layout below all other child views,
     * for internal implementation use only,
     * for example, a ImageView's implementation may use native view
     * and set it as internalNativeView\n
     * subclass must not override parent,
     * if really necessary, use #internalBackgroundViewAdd\n
     * use with caution
     * @see nativeView
     */
    ZFMETHOD_DECLARE_0(void *, nativeImplView);
protected:
    /**
     * @brief see #nativeImplView
     */
    zffinal void nativeImplViewSet(ZF_IN void *nativeImplView,
                                   ZF_IN ZFUIViewNativeImplViewDeleteCallback nativeImplViewDeleteCallback);
    /**
     * @brief called to layout native impl view, which would fill parent by default
     *
     * you may override default behavior without calling super
     */
    virtual inline void nativeImplViewOnLayout(ZF_OUT ZFUIRect &result,
                                               ZF_IN const ZFUIRect &bounds)
    {
    }
    /**
     * @brief update native impl view's margin
     *
     * call #nativeImplViewMarginOnUpdate to update the margin value,
     * for subclass to achieve complex layout logic\n
     * the margin won't be update automatically for performance,
     * subclass should manually call this method if necessary
     */
    zffinal void nativeImplViewMarginUpdate(void);
    /**
     * @brief see #nativeImplViewMarginUpdate
     */
    virtual inline void nativeImplViewMarginOnUpdate(ZF_IN_OUT ZFUIMargin &nativeImplViewMargin)
    {
    }
    /**
     * @brief access the margin without update it, see #nativeImplViewMarginUpdate
     */
    zffinal const ZFUIMargin &nativeImplViewMargin(void);

    // ============================================================
protected:
    /**
     * @brief called to add or remove view to impl
     *
     * subclass may override this method to add child to other container\n
     * to implement this, you must implement all these methods:
     * -  #implChildOnAdd : called to add to impl
     * -  #implChildOnRemove : called to remove from impl
     */
    virtual void implChildOnAdd(ZF_IN ZFUIView *child,
                                ZF_IN zfindex virtualIndex,
                                ZF_IN ZFUIViewChildLayerEnum childLayer,
                                ZF_IN zfindex childLayerIndex);
    /**
     * @brief see #implChildOnAdd
     */
    virtual void implChildOnRemove(ZF_IN ZFUIView *child,
                                   ZF_IN zfindex virtualIndex,
                                   ZF_IN ZFUIViewChildLayerEnum childLayer,
                                   ZF_IN zfindex childLayerIndex);

public:
    /**
     * @brief native container view
     *
     * the actual type of this is defined by implementation,
     * and it's not recommended to use in your application\n
     * \n
     * for how to add ZFUIView to native view, please refer to #ZFUIView\n
     * for how to add native view to ZFUIView, please refer to #ZFUINativeViewWrapper\n
     * for how to access native implementation, please refer to #nativeImplView
     */
    ZFMETHOD_DECLARE_0(void *, nativeView);
    static void _ZFP_ZFUIView_nativeViewNotifyAdd(ZF_IN ZFUIView *view, ZF_IN void *nativeParentView);
    static void _ZFP_ZFUIView_nativeViewNotifyRemove(ZF_IN ZFUIView *view);

    // ============================================================
    // view delegate logic
protected:
    /**
     * @brief manually set the view delegate, see #ZFUIView::viewDelegateClass
     *
     * note, this method is not serializable,
     * this method and #ZFUIView::viewDelegateClass is exclusive
     * and would override with each other\n
     * this method is not affected by #viewDelegateSupported
     */
    virtual void viewDelegateSet(ZF_IN ZFUIView *viewDelegate);
    /**
     * @brief whether this view support delegate view logic
     */
    virtual inline zfbool viewDelegateSupported(void)
    {
        return zftrue;
    }
public:
    /**
     * @brief true if this view is a delegate view for parent
     */
    ZFMETHOD_DECLARE_0(zfbool, viewDelegateForParent);
    /**
     * @brief delegate parent of this view, null if this view is added normally
     * @see viewParent, viewParentVirtual
     */
    ZFMETHOD_DECLARE_0(ZFUIView *, viewDelegateParent);
    /**
     * @brief see #ZFUIView::viewDelegateClass
     */
    ZFMETHOD_DECLARE_0(ZFUIView *, viewDelegate);
    /**
     * @brief util method to #viewDelegate
     */
    template<typename T_ZFObject>
    inline T_ZFObject viewDelegate(void)
    {
        return ZFCastZFObjectUnchecked(T_ZFObject, this->viewDelegate());
    }
protected:
    /**
     * @brief called to init delegate view
     */
    virtual inline void viewDelegateOnInit(ZF_IN ZFUIView *viewDelegate)
    {
    }
    /**
     * @brief called to destroy delegate view
     */
    virtual inline void viewDelegateOnDealloc(ZF_IN ZFUIView *viewDelegate)
    {
    }
    /**
     * @brief see ##ZFUIView::viewDelegateClass, #layoutOnMeasure
     */
    virtual void viewDelegateLayoutOnMeasure(ZF_OUT ZFUISize &ret,
                                             ZF_IN const ZFUISize &sizeHint,
                                             ZF_IN const ZFUISizeParam &sizeParam);
    /**
     * @brief see ##ZFUIView::viewDelegateClass, #layoutOnMeasureFinish
     */
    virtual void viewDelegateLayoutOnMeasureFinish(ZF_IN_OUT ZFUISize &measuredSize,
                                                   ZF_IN const ZFUISize &sizeHint,
                                                   ZF_IN const ZFUISizeParam &sizeParam);
    /**
     * @brief see ##ZFUIView::viewDelegateClass, #layoutOnLayoutPrepare
     */
    virtual void viewDelegateLayoutOnLayoutPrepare(ZF_IN const ZFUIRect &bounds);
    /**
     * @brief see ##ZFUIView::viewDelegateClass, #layoutOnLayout
     */
    virtual void viewDelegateLayoutOnLayout(ZF_IN const ZFUIRect &bounds);
    /**
     * @brief see ##ZFUIView::viewDelegateClass, #layoutOnLayoutFinish
     */
    virtual void viewDelegateLayoutOnLayoutFinish(ZF_IN const ZFUIRect &bounds);

    // ============================================================
    // view focus
public:
    /**
     * @brief whether the view currently focused
     */
    ZFMETHOD_DECLARE_0(zfbool, viewFocused);
    /**
     * @brief request to obtain or resign focus,
     *   result can be checked by #viewFocused
     *
     * only focused view can receive key events
     */
    ZFMETHOD_DECLARE_1(void, viewFocusRequest,
                       ZFMP_IN(zfbool, viewFocus));
    zffinal void _ZFP_ZFUIView_viewFocusOnChange(void)
    {
        this->viewFocusOnChange();
    }
    /**
     * @brief return focused child (or this view) or null if nothing focused
     *   or ZFUIViewFocus implementation not available
     *
     * @note this method would recursively search all children (including internal views)
     *   to find the focused child,
     *   take care of the performance for huge view tree
     */
    ZFMETHOD_DECLARE_0(ZFUIView *, viewFocusedChild);
protected:
    /** @brief see #EventViewFocusOnChange */
    virtual inline void viewFocusOnChange(void)
    {
        this->observerNotify(ZFUIView::EventViewFocusOnChange());
    }

    // ============================================================
    // parent
public:
    zffinal void _ZFP_ZFUIView_parentChanged(ZF_IN ZFUIView *parentView,
                                             ZF_IN ZFUIViewLayoutParam *layoutParam,
                                             ZF_IN ZFUIViewChildLayerEnum viewLayer);
    /**
     * @brief parent view or null if none
     * @see viewParentVirtual, viewDelegateParent
     */
    ZFMETHOD_DECLARE_0(ZFUIView *, viewParent);
    /**
     * @brief return #viewDelegateParent if exist, or #viewParent otherwise
     */
    ZFMETHOD_DECLARE_0(ZFUIView *, viewParentVirtual);

    /**
     * @brief remove this view from parent or do nothing if no parent
     *
     * can remove normal child view or internal view
     */
    ZFMETHOD_DECLARE_0(void, viewRemoveFromParent);

    // ============================================================
    // scale settings
public:
    /**
     * @brief scale for view
     *
     * ZFUIView use a special scale logic to adapt various screen sizes,
     * which contain these scale values:
     * -  app scale:\n
     *   accessed by #scaleGet, 1 by default\n
     *   automatically changed while adding a ZFUIView to another,
     *   and can only be changed by app by using #ZFUIRootView::scaleSet of #ZFUISysWindow
     * -  impl scale:\n
     *   accessed by #scaleGetForImpl, it's value depends on impl\n
     *   automatically changed while adding a ZFUIView to native view,
     *   can not be changed by app
     * -  fixed scale:\n
     *   accessed by #scaleGetFixed, always equal to (#scaleGet * #scaleGetForImpl)\n
     *   all size unit would be applied with this value
     *   before passing to implementations,
     *   can not be changed by app
     * -  impl physical scale:\n
     *   accessedb y #scaleGetForImplPhysicalPixel, it's value depends on impl\n
     *   corresponding to #scaleGetForImpl,
     *   used only if you want to verify physical pixel
     *   (since impl may have it's own scale logic)
     *
     * in general:
     * -  for app:\n
     *   usually you have no need to worry about scales,
     *   all elements can be assigned as fixed size,
     *   such as 48 for a button's height and 21 for a small textView's height,
     *   it will be scaled automatically while rendering to different size's or DPI's devices\n
     *   if you really want to change scale setting,
     *   you should use #ZFUIRootView::scaleSet of #ZFUISysWindow
     * -  for implementation:\n
     *   you have no need to worry about element's logical size,
     *   everything would be scaled to desired size unit
     *   depending on the scale value that impl returned
     *
     * \n
     * since scale may affect impl's pixel size,
     * size-related property should be flushed manually while scale changed,
     * subclass should override #scaleOnChange to update them,
     * which would be called if #scaleGetFixed really changed
     */
    ZFMETHOD_DECLARE_0(zffloat, scaleGet);
    /**
     * @brief see #scaleGet
     */
    ZFMETHOD_DECLARE_0(zffloat, scaleGetForImpl);
    /**
     * @brief see #scaleGet
     */
    ZFMETHOD_DECLARE_0(zffloat, scaleGetForImplPhysicalPixel);
    /**
     * @brief see #scaleGet
     */
    ZFMETHOD_DECLARE_0(zffloat, scaleGetFixed);
protected:
    /**
     * @brief see #scaleGet, ensured called only when scale value actually changed
     *
     * after this method, #EventViewScaleOnChange would be fired
     */
    virtual void scaleOnChange(void);
public:
    void _ZFP_ZFUIView_scaleSet(ZF_IN zffloat scaleFixed,
                                ZF_IN zffloat scaleForImpl);
    void _ZFP_ZFUIView_scaleSetRecursively(ZF_IN zffloat scaleFixed,
                                           ZF_IN zffloat scaleForImpl);

    // ============================================================
    // layout logic
public:
    /**
     * @brief create layout param,
     *   calling #layoutParamClass to create instance
     *   and #layoutParamOnUpdate to update
     */
    ZFMETHOD_DECLARE_0(zfautoObject, layoutParamCreate);
protected:
    /**
     * @brief see #layoutParamCreate
     *
     * you should override this method to declare your layout param class
     */
    virtual const ZFClass *layoutParamClass(void);
    /**
     * @brief see #layoutParamCreate
     */
    virtual inline void layoutParamOnUpdate(ZF_IN ZFUIViewLayoutParam *layoutParam)
    {
    }

public:
    /**
     * @brief manually set layout param
     *
     * this method can be called even if this view has no parent,
     * the layout param would be serialized while serializing the view itself\n
     * while adding to another container view with different layout param type,
     * a new layout param would be created and applied style from the existing one
     */
    ZFMETHOD_DECLARE_1(void, layoutParamSet,
                       ZFMP_IN(ZFUIViewLayoutParam *, layoutParam));
    /**
     * @brief get self's layout param, valid only while the view has parent
     *
     * return null if the view has no parent,
     * automatically invoke the view's #layoutRequest if the layout param's property changed
     */
    ZFMETHOD_DECLARE_0(ZFUIViewLayoutParam *, layoutParam);
    /**
     * @brief see #layoutParam
     */
    template<typename T_LayoutParam>
    T_LayoutParam layoutParam(void)
    {
        return ZFCastZFObjectUnchecked(T_LayoutParam, this->layoutParam());
    }
    /**
     * @brief #ZFAnyT version of #layoutParam
     */
    zffinal inline ZFAnyT<ZFUIViewLayoutParam *> layoutParamT(void)
    {
        return ZFAnyT<ZFUIViewLayoutParam *>(this->layoutParam());
    }

public:
    zffinal void _ZFP_ZFUIView_notifyLayoutRootView(ZF_IN const ZFUIRect &bounds);
    /**
     * @brief override #layoutRequest to prevent this view being layouted for some condition
     *
     * this method is useful if you want to update some property without notifying the view,
     * typically for performance only, use with caution
     */
    ZFMETHOD_DECLARE_1(void, layoutRequestOverrideSet,
                       ZFMP_IN(zfbool, layoutRequestOverride));
    /**
     * @brief see #layoutRequestOverrideSet
     */
    ZFMETHOD_DECLARE_0(zfindex, layoutRequestOverride);
    /**
     * @brief set need layout
     */
    ZFMETHOD_DECLARE_0(void, layoutRequest);
    /**
     * @brief true if need layout
     */
    ZFMETHOD_DECLARE_0(zfbool, layoutRequested);
    /**
     * @brief true if currently being layouted
     */
    ZFMETHOD_DECLARE_0(zfbool, layouting);
    /**
     * @brief measure the view
     *
     * call #layoutOnMeasure to see the needed size for this view\n
     * note that internal views won't be measured
     * @see layoutMeasuredSize
     */
    ZFMETHOD_DECLARE_2(const ZFUISize &, layoutMeasure,
                       ZFMP_IN(const ZFUISize &, sizeHint),
                       ZFMP_IN(const ZFUISizeParam &, sizeParam));
    /**
     * @brief get measured size, invalid if not measured
     */
    ZFMETHOD_DECLARE_0(const ZFUISize &, layoutMeasuredSize);
    /**
     * @brief layout the view and it's children
     *
     * internal views have layout step but no measure step
     */
    ZFMETHOD_DECLARE_1(void, layout,
                       ZFMP_IN(const ZFUIRect &, rect));
    /**
     * @brief force to layout if need
     */
    ZFMETHOD_DECLARE_0(void, layoutIfNeed);
    /**
     * @brief get the frame of this view, invalid if not layout
     */
    ZFMETHOD_DECLARE_0(const ZFUIRect &, layoutedFrame);
    /**
     * @brief get previous frame of this view, ensured zero for first time,
     *   ensured reset to zero after remove from parent
     *
     * you may also reset it manually by #layoutedFramePrevReset
     */
    ZFMETHOD_DECLARE_0(const ZFUIRect &, layoutedFramePrev);
    /**
     * @brief manually reset #layoutedFramePrev to zero
     */
    ZFMETHOD_DECLARE_0(void, layoutedFramePrevReset);
    /**
     * @brief get fixed frame of this view, invalid if not layout
     *
     * for views that have offset logic (typically scroll views),
     * use this method to access frame relative to its parent
     * instead of frame applied with offset\n
     * call this method would cause parent's #layoutedFrameFixedOnUpdateForChild being called
     * to update the actual frame,
     * result may be invalid if not layout or parent is not type of ZFUIView,
     * in this case, #layoutedFrame would be returned
     */
    ZFMETHOD_DECLARE_1(void, layoutedFrameFixedT,
                       ZFMP_OUT(ZFUIRect &, ret));
    /**
     * @brief see #layoutedFrameFixed
     */
    ZFMETHOD_DECLARE_0(ZFUIRect, layoutedFrameFixed)
    {
        ZFUIRect ret = ZFUIRectZero();
        this->layoutedFrameFixedT(ret);
        return ret;
    }
protected:
    /**
     * @brief called by #layoutMeasure to decide the view's size
     *
     * you may override without call super to supply your own layout logic\n
     * \n
     * note that we doesn't ensure layoutOnMeasure would be called before layoutOnLayout,
     * actually, we doesn't ensure layoutOnMeasure would be called,
     * only layout that has wrap content features may call #layoutMeasure
     * to calculate children's size\n
     * \n
     * what sizeHint means, depends on sizeParam, see #ZFUISizeType for more info\n
     * \n
     * return a negative value means the view doesn't care about size,
     * let #ZFUIView::viewSizePrefered to decide final result size\n
     * \n
     * @note there's some repeatly work that #layoutMeasure would have done for you,
     *   you should not repeat it again for performance:
     *   -  filter out the case that both sizeParam are fixed or fill parent
     *   -  apply sizeHint by #ZFUIViewLayoutParam::sizeHintApply
     *   -  fix result size in range [viewSizeMin, viewSizeMax]
     */
    virtual inline void layoutOnMeasure(ZF_OUT ZFUISize &ret,
                                        ZF_IN const ZFUISize &sizeHint,
                                        ZF_IN const ZFUISizeParam &sizeParam)
    {
    }
    /** @brief see #EventViewLayoutOnMeasureFinish */
    virtual inline void layoutOnMeasureFinish(ZF_IN_OUT ZFUISize &measuredSize,
                                              ZF_IN const ZFUISize &sizeHint,
                                              ZF_IN const ZFUISizeParam &sizeParam)
    {
    }
    /** @brief see #EventViewLayoutOnLayoutPrepare */
    virtual inline void layoutOnLayoutPrepare(ZF_IN const ZFUIRect &bounds)
    {
    }
    /**
     * @brief called by #layout to layout the view and children
     *
     * it's valid for subclass to override without calling zfsuper::layoutOnLayout,
     * which means subclass would override all layout steps in parent\n
     * \n
     * note that we doesn't ensure layoutOnMeasure would be called before layoutOnLayout
     */
    virtual void layoutOnLayout(ZF_IN const ZFUIRect &bounds);
    /** @brief see #EventViewLayoutOnLayoutFinish */
    virtual inline void layoutOnLayoutFinish(ZF_IN const ZFUIRect &bounds)
    {
    }
    /**
     * @brief for subclass to impl #layoutedFrameFixed
     */
    virtual inline void layoutedFrameFixedOnUpdateForChild(ZF_OUT ZFUIRect &ret, ZF_IN const ZFUIRect &childFrame)
    {
        ret = childFrame;
    }

    // ============================================================
    // children management
public:
    /**
     * @brief find view by viewId, return the view or null if not found
     */
    ZFMETHOD_DECLARE_3(ZFUIView *, childFindById,
                       ZFMP_IN(const zfchar *, viewId),
                       ZFMP_IN_OPT(zfbool, findRecursively, zftrue),
                       ZFMP_IN_OPT(zfbool, includeInternalViews, zffalse));

public:
    /**
     * @brief add view with layout param, param must be created by #layoutParamCreate
     *
     * if layoutParam is null (by default), create new one by #layoutParamCreate\n
     * if layoutParam is type of #layoutParamClass and not null, it would be used directly,
     * otherwise, a new layout param would be created
     * and source layout param would be copied to the newly created layout param
     */
    ZFMETHOD_DECLARE_3(void, childAdd,
                       ZFMP_IN(ZFUIView *, view),
                       ZFMP_IN_OPT(ZFUIViewLayoutParam *, layoutParam, zfnull),
                       ZFMP_IN_OPT(zfindex, atIndex, zfindexMax()));
    /**
     * @brief remove view or do nothing if view isn't added to this view
     */
    ZFMETHOD_DECLARE_1(void, childRemove,
                       ZFMP_IN(ZFUIView *, view));
    /**
     * @brief remove view at index or assert fail if index out of range
     */
    ZFMETHOD_DECLARE_1(void, childRemoveAtIndex,
                       ZFMP_IN(zfindex, index));
    /**
     * @brief remove all child view
     */
    ZFMETHOD_DECLARE_0(void, childRemoveAll);
    /**
     * @brief move view, make toIndexOrIndexMax as zfindexMax() to move to top most,
     *   and 0 to bottom most, do nothing if index invalid or have no change
     *
     * assert fail if fromIndex out of range, or toIndexOrIndexMax isn't zfindexMax() and out of range\n
     * moving a view would cause #layoutRequest being called
     */
    ZFMETHOD_DECLARE_2(void, childMove,
                       ZFMP_IN(zfindex, fromIndex),
                       ZFMP_IN(zfindex, toIndexOrIndexMax));
    /**
     * @brief see #childMove
     */
    ZFMETHOD_DECLARE_2(void, childMove,
                       ZFMP_IN(ZFUIView *, child),
                       ZFMP_IN(zfindex, toIndexOrIndexMax));
    /**
     * @brief replace child at index, assert fail if index out of range
     *   or view to replace already has parent
     */
    ZFMETHOD_DECLARE_2(void, childReplaceAtIndex,
                       ZFMP_IN(zfindex, atIndex),
                       ZFMP_IN(ZFUIView *, toReplace));
    /**
     * @brief get child view count
     */
    ZFMETHOD_DECLARE_0(zfindex, childCount);
    /**
     * @brief get child view at index or assert fail if out of range
     */
    ZFMETHOD_DECLARE_1(ZFUIView *, childAtIndex,
                       ZFMP_IN(zfindex, index));
    /**
     * @brief return index of view or zfindexMax() if not child of this view
     */
    ZFMETHOD_DECLARE_1(zfindex, childFind,
                       ZFMP_IN(ZFUIView *, view));
    /**
     * @brief get the child view array
     */
    ZFMETHOD_DECLARE_0(ZFCoreArrayPOD<ZFUIView *>, childArray);

    /**
     * @brief this view belongs to which layer of parent,
     *   valid only if #viewParent is not null
     *
     * would be #ZFUIViewChildLayer::e_Normal if no parent
     */
    ZFMETHOD_DECLARE_0(ZFUIViewChildLayerEnum, viewLayer);
    /**
     * @brief return all children including internal views, see #childArray
     *
     * children are ensured ordered by (impl, bg, normal, fg) views
     */
    ZFMETHOD_DECLARE_0(ZFCoreArrayPOD<ZFUIView *>, childRawArray);

    // ============================================================
    // events
protected:
    /** @brief see #EventViewChildOnChange */
    virtual void viewChildOnChange(void);
    /** @brief see #EventViewChildOnAdd */
    virtual void viewChildOnAdd(ZF_IN ZFUIView *child,
                                ZF_IN ZFUIViewChildLayerEnum layer);
    /** @brief see #EventViewChildOnRemove */
    virtual void viewChildOnRemove(ZF_IN ZFUIView *child,
                                   ZF_IN ZFUIViewChildLayerEnum layer);
    /** @brief see #EventViewOnAddToParent */
    virtual void viewOnAddToParent(ZF_IN ZFUIView *parent);
    /** @brief see #EventViewOnRemoveFromParent */
    virtual void viewOnRemoveFromParent(ZF_IN ZFUIView *parent);

    // ============================================================
    // internal impl views
public:
    /** @brief see #internalBackgroundViewAdd */
    ZFMETHOD_DECLARE_3(void, internalImplViewAdd,
                       ZFMP_IN(ZFUIView *, view),
                       ZFMP_IN_OPT(ZFUIViewLayoutParam *, layoutParam, zfnull),
                       ZFMP_IN_OPT(zfbool, addAsTopMost, zftrue));
    /** @brief see #internalBackgroundViewAdd */
    ZFMETHOD_DECLARE_1(void, internalImplViewRemove,
                       ZFMP_IN(ZFUIView *, view));
    /** @brief see #internalBackgroundViewAdd */
    ZFMETHOD_DECLARE_0(ZFCoreArrayPOD<ZFUIView *>, internalImplViewArray);
protected:
    /** @brief see #internalBackgroundViewAdd */
    virtual void internalImplViewOnLayout(ZF_IN const ZFUIRect &bounds);

    // ============================================================
    // internal background views
public:
    /**
     * @brief internal view which is independent from normal view
     *
     * we have these layers in ZFUIView module:
     * -  internal impl view
     * -  internal background view
     * -  normal view
     * -  internal foreground view
     *
     * each layer is independent and has the same interface to add or remove view\n
     * to make the interfaces cleaner, the internal ones are named with
     * "internalBackgroundView" and "internalForegroundView" as pre-fix,
     * such as #internalBackgroundViewAdd and #internalBackgroundViewRemove
     * (considering the #childAdd and #childRemove)\n
     * \n
     * internal views has no measure steps, its size always depends on parent's size\n
     * \n
     * for safety, internal views has no access methods related to index
     * subclass should save internal views as member and access manually\n
     * also, subclass must call super's method when override internalXXX
     */
    ZFMETHOD_DECLARE_3(void, internalBackgroundViewAdd,
                       ZFMP_IN(ZFUIView *, view),
                       ZFMP_IN_OPT(ZFUIViewLayoutParam *, layoutParam, zfnull),
                       ZFMP_IN_OPT(zfbool, addAsTopMost, zftrue));
    /** @brief see #internalBackgroundViewAdd */
    ZFMETHOD_DECLARE_1(void, internalBackgroundViewRemove,
                       ZFMP_IN(ZFUIView *, view));
    /**
     * @brief usually for debug use only, try to avoid use this in your app for other purpose
     */
    ZFMETHOD_DECLARE_0(ZFCoreArrayPOD<ZFUIView *>, internalBackgroundViewArray);
protected:
    /** @brief see #internalBackgroundViewAdd */
    virtual void internalBackgroundViewOnLayout(ZF_IN const ZFUIRect &bounds);

    // ============================================================
    // internal foreground views
public:
    /** @brief see #internalBackgroundViewAdd */
    ZFMETHOD_DECLARE_3(void, internalForegroundViewAdd,
                       ZFMP_IN(ZFUIView *, view),
                       ZFMP_IN_OPT(ZFUIViewLayoutParam *, layoutParam, zfnull),
                       ZFMP_IN_OPT(zfbool, addAsTopMost, zftrue));
    /** @brief see #internalBackgroundViewAdd */
    ZFMETHOD_DECLARE_1(void, internalForegroundViewRemove,
                       ZFMP_IN(ZFUIView *, view));
    /** @brief see #internalBackgroundViewAdd */
    ZFMETHOD_DECLARE_0(ZFCoreArrayPOD<ZFUIView *>, internalForegroundViewArray);
    /** @brief see #internalBackgroundViewAdd */
    virtual void internalForegroundViewOnLayout(ZF_IN const ZFUIRect &bounds);

    // ============================================================
    // other internal view logic
public:
    /**
     * @brief used to apply auto serialize logic to internal views
     *
     * by default, internal views won't be serialized automatically,
     * you may make it available by:
     * -  have internal view's viewId set
     * -  have same id set by this method
     *
     * while serializing, if an internal view with same id already exists,
     * we would copy style from serialize data to the existing one instead
     */
    ZFMETHOD_DECLARE_1(void, internalViewAutoSerializeTagAdd,
                       ZFMP_IN(const zfchar *, tag));
    /** @brief see #internalViewAutoSerializeTagAdd */
    ZFMETHOD_DECLARE_1(void, internalViewAutoSerializeTagRemove,
                       ZFMP_IN(const zfchar *, tag));
    /** @brief see #internalViewAutoSerializeTagAdd */
    ZFMETHOD_DECLARE_0(void, internalViewAutoSerializeTagRemoveAll);
    /** @brief see #internalViewAutoSerializeTagAdd */
    ZFMETHOD_DECLARE_1(void, internalViewAutoSerializeTagGetAllT,
                       ZFMP_OUT(ZFCoreArray<zfstring> &, ret));
    /** @brief see #internalViewAutoSerializeTagAdd */
    ZFMETHOD_DECLARE_0(ZFCoreArray<zfstring>, internalViewAutoSerializeTagGetAll)
    {
        ZFCoreArray<zfstring> ret;
        this->internalViewAutoSerializeTagGetAllT(ret);
        return ret;
    }
protected:
    /**
     * @brief called to check whether the view should be layouted using default layout logic,
     *   return true by default
     */
    virtual zfbool internalViewShouldLayout(ZF_IN ZFUIView *internalView);

    // ============================================================
    // UI events
public:
    /**
     * @brief directly send a event, use with caution
     */
    ZFMETHOD_DECLARE_1(void, viewEventSend,
                       ZFMP_IN(ZFUIEvent *, event));
protected:
    /**
     * @brief see #EventViewOnEventFilter
     */
    virtual inline void viewEventOnEventFilter(ZF_IN ZFUIEvent *event)
    {
    }
    /**
     * @brief notified when a ZFUIEvent occurred
     *
     * default behavior is to dispatch event depends on event type\n
     * you may override without call super's method, to override the event\n
     * you should update #ZFEvent::eventResolved if resolved
     */
    virtual void viewEventOnEvent(ZF_IN ZFUIEvent *event);

    // ============================================================
    // events
protected:
    /**
     * @brief called when mouse event occurred
     *
     * due to some limitations, we doesn't support intercept mouse event,
     * event dispatch logic depends on implementation,
     * you may use native view to achieve if necessary\n
     * \n
     * mouse hover event would only be fired if #viewMouseHoverEventEnable\n
     * \n
     * by default, this method would simply resolve the event if this view is enabled,
     * you may override without call super's method, to override the event
     */
    virtual void viewEventOnMouseEvent(ZF_IN ZFUIMouseEvent *mouseEvent);

    /**
     * @brief called when key occurred
     *
     * due to some limitations, we doesn't support intercept key event,
     * event dispatch logic depends on implementation,
     * you may use native view to achieve if necessary\n
     * \n
     * by default, this method would call #viewEventOnKeyEventResolveFocus to achieve focus move,
     * you may override without call super's method, to override the event\n
     * the event would be dispatched from child to parent,
     * util it's resolved
     */
    virtual void viewEventOnKeyEvent(ZF_IN ZFUIKeyEvent *keyEvent);
    /**
     * @brief called by #viewEventOnKeyEvent to resolve focus move key event
     *
     * this method would call #ZFUIViewFocusResolveKeyEvent to achieve focus move,
     * you may override without call super's method, to override the event
     */
    virtual void viewEventOnKeyEventResolveFocus(ZF_IN ZFUIKeyEvent *keyEvent);

    /**
     * @brief called when wheel event occurred
     *
     * due to some limitations, we doesn't support intercept wheel event,
     * event dispatch logic depends on implementation,
     * you may use native view to achieve if necessary\n
     * \n
     * the event would be dispatched from child to parent,
     * util it's resolved
     */
    virtual void viewEventOnWheelEvent(ZF_IN ZFUIWheelEvent *wheelEvent);

    // ============================================================
    // view property async update
public:
    /**
     * @brief schedule a update task that #viewPropertyOnUpdate would be called after a proper time,
     *   used to update view's property,
     *   ensured called after a view created
     */
    ZFMETHOD_DECLARE_0(void, viewPropertyUpdateRequest);
    zffinal inline void _ZFP_ZFUIView_viewPropertyNotifyUpdate(void)
    {
        this->viewPropertyOnUpdate();
    }
protected:
    /** @brief see #viewPropertyUpdateRequest */
    virtual void viewPropertyOnUpdate(void);

    // ============================================================
    // override
protected:
    zfoverride
    virtual void observerOnAdd(ZF_IN const zfidentity &eventId);
    zfoverride
    virtual void observerOnRemove(ZF_IN const zfidentity &eventId);

private:
    _ZFP_ZFUIViewPrivate *d;
    friend zfclassFwd _ZFP_ZFUIViewPrivate;
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFUIView_h_

#include "ZFUIViewFocus.h"
#include "ZFUIViewTreePrint.h"
#include "ZFUIViewUtil.h"

