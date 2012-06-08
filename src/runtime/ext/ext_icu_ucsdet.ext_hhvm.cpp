#include <runtime/ext_hhvm/ext_hhvm.h>
#include <runtime/base/builtin_functions.h>
#include <runtime/base/array/array_init.h>
#include <runtime/ext/ext.h>
#include <runtime/vm/class.h>
#include <runtime/vm/runtime.h>
#include <runtime/vm/exception_gate.h>
#include <exception>

namespace HPHP {

class c_EncodingDetector_Instance : public c_EncodingDetector {
public:
  c_EncodingDetector_Instance (HPHP::VM::Class* cls, unsigned nProps) {
    DECLARE_STACK_GC_ROOT(ObjectData, this);
    m_cls = cls;
    setAttributes(cls->getODAttrs()
                  | (cls->clsInfo()
                     ? 0 : IsInstance));
    m_propVec = (TypedValue *)((uintptr_t)this + sizeof(c_EncodingDetector));
    if (cls->needInitialization()) {
      cls->initialize();
    }
    if (nProps > 0) {
      if (cls->pinitVec().size() > 0) {
        initialize(nProps);
      } else {
        ASSERT(nProps == cls->declPropInit().size());
        memcpy(m_propVec, &cls->declPropInit()[0], nProps * sizeof(TypedValue));
      }
    }
  }
  static HPHP::VM::Instance* new_Instance(HPHP::VM::Class* cls) {
    size_t nProps = cls->numDeclProperties();
    size_t builtinPropSize = sizeof(c_EncodingDetector) - sizeof(ObjectData);
    size_t size = sizeForNProps(nProps) + builtinPropSize;
    HPHP::VM::Instance *inst = (HPHP::VM::Instance*)ALLOCOBJSZ(size);
    new ((void *)inst) c_EncodingDetector_Instance(cls, nProps);
    return inst;
  }
  void operator delete(void *p) {
    c_EncodingDetector_Instance *this_ = (c_EncodingDetector_Instance*)p;
    size_t nProps = this_->m_cls->numDeclProperties();
    size_t builtinPropSize UNUSED = sizeof(c_EncodingDetector) - sizeof(ObjectData);
    if (this_->m_propMap) {
      this_->m_propMap->release();
    }
    for (size_t i = 0; i < nProps; ++i) {
      TypedValue *prop = &this_->m_propVec[i];
      tvRefcountedDecRef(prop);
    }
    DELETEOBJSZ(sizeForNProps(nProps) + builtinPropSize)(this_);
  }
  virtual bool o_instanceof(const HPHP::String& s) const {
    return Instance::o_instanceof(s) || c_EncodingDetector::o_instanceof(s);
  }
  virtual Variant* o_realProp(CStrRef s, int flags, CStrRef context) const {
    Variant *v = Instance::o_realProp(s, flags, context);
    if (v) return v;
    return c_EncodingDetector::o_realProp(s, flags, context);
  }
  virtual Variant* o_realPropPublic(CStrRef s, int flags) const {
    Variant *v = Instance::o_realPropPublic(s, flags);
    if (v) return v;
    return c_EncodingDetector::o_realPropPublic(s, flags);
  }
  virtual void o_setArray(CArrRef props) {
    ClassInfo::SetArray(this, o_getClassPropTable(), props);
  }
  virtual void o_getArray(Array &props, bool pubOnly) const {
    ClassInfo::GetArray(this, o_getClassPropTable(), props, false);
}
  virtual ObjectData* cloneImpl() {
    return Instance::cloneImpl();
  }
  virtual void cloneSet(ObjectData *clone) {
    c_EncodingDetector::cloneSet(clone);
    Instance::cloneSet(clone);
  }
};

HPHP::VM::Instance* new_EncodingDetector_Instance(HPHP::VM::Class* cls) {
  return c_EncodingDetector_Instance::new_Instance(cls);
}

/*
void HPHP::c_EncodingDetector::t___construct()
_ZN4HPHP18c_EncodingDetector13t___constructEv

this_ => rdi
*/

void th_16EncodingDetector___construct(ObjectData* this_) asm("_ZN4HPHP18c_EncodingDetector13t___constructEv");

TypedValue* tg_16EncodingDetector___construct(HPHP::VM::ActRec *ar) {
  EXCEPTION_GATE_ENTER();
    TypedValue rv;
    long long count = ar->numArgs();
    TypedValue* args UNUSED = ((TypedValue*)ar) - 1;
    ObjectData* this_ = (ar->hasThis() ? ar->getThis() : NULL);
    if (this_) {
      if (count == 0LL) {
        rv.m_data.num = 0LL;
        rv._count = 0;
        rv.m_type = KindOfNull;
        th_16EncodingDetector___construct((this_));
        frame_free_locals_inl(ar, 0);
        memcpy(&ar->m_r, &rv, sizeof(TypedValue));
        return &ar->m_r;
      } else {
        throw_toomany_arguments_nr("EncodingDetector::__construct", 0, 1);
      }
    } else {
      throw_instance_method_fatal("EncodingDetector::__construct");
    }
    rv.m_data.num = 0LL;
    rv._count = 0;
    rv.m_type = KindOfNull;
    frame_free_locals_inl(ar, 0);
    memcpy(&ar->m_r, &rv, sizeof(TypedValue));
    return &ar->m_r;
  EXCEPTION_GATE_RETURN(&ar->m_r);
}

/*
void HPHP::c_EncodingDetector::t_settext(HPHP::String const&)
_ZN4HPHP18c_EncodingDetector9t_settextERKNS_6StringE

this_ => rdi
text => rsi
*/

void th_16EncodingDetector_setText(ObjectData* this_, Value* text) asm("_ZN4HPHP18c_EncodingDetector9t_settextERKNS_6StringE");

TypedValue* tg1_16EncodingDetector_setText(TypedValue* rv, HPHP::VM::ActRec* ar, long long count, ObjectData* this_) __attribute__((noinline,cold));
TypedValue* tg1_16EncodingDetector_setText(TypedValue* rv, HPHP::VM::ActRec* ar, long long count, ObjectData* this_) {
  TypedValue* args UNUSED = ((TypedValue*)ar) - 1;
  rv->m_data.num = 0LL;
  rv->_count = 0;
  rv->m_type = KindOfNull;
  tvCastToStringInPlace(args-0);
  th_16EncodingDetector_setText((this_), (Value*)(args-0));
  return rv;
}

TypedValue* tg_16EncodingDetector_setText(HPHP::VM::ActRec *ar) {
  EXCEPTION_GATE_ENTER();
    TypedValue rv;
    long long count = ar->numArgs();
    TypedValue* args UNUSED = ((TypedValue*)ar) - 1;
    ObjectData* this_ = (ar->hasThis() ? ar->getThis() : NULL);
    if (this_) {
      if (count == 1LL) {
        if (IS_STRING_TYPE((args-0)->m_type)) {
          rv.m_data.num = 0LL;
          rv._count = 0;
          rv.m_type = KindOfNull;
          th_16EncodingDetector_setText((this_), (Value*)(args-0));
          frame_free_locals_inl(ar, 1);
          memcpy(&ar->m_r, &rv, sizeof(TypedValue));
          return &ar->m_r;
        } else {
          tg1_16EncodingDetector_setText(&rv, ar, count , this_);
          frame_free_locals_inl(ar, 1);
          memcpy(&ar->m_r, &rv, sizeof(TypedValue));
          return &ar->m_r;
        }
      } else {
        throw_wrong_arguments_nr("EncodingDetector::setText", count, 1, 1, 1);
      }
    } else {
      throw_instance_method_fatal("EncodingDetector::setText");
    }
    rv.m_data.num = 0LL;
    rv._count = 0;
    rv.m_type = KindOfNull;
    frame_free_locals_inl(ar, 1);
    memcpy(&ar->m_r, &rv, sizeof(TypedValue));
    return &ar->m_r;
  EXCEPTION_GATE_RETURN(&ar->m_r);
}

/*
void HPHP::c_EncodingDetector::t_setdeclaredencoding(HPHP::String const&)
_ZN4HPHP18c_EncodingDetector21t_setdeclaredencodingERKNS_6StringE

this_ => rdi
text => rsi
*/

void th_16EncodingDetector_setDeclaredEncoding(ObjectData* this_, Value* text) asm("_ZN4HPHP18c_EncodingDetector21t_setdeclaredencodingERKNS_6StringE");

TypedValue* tg1_16EncodingDetector_setDeclaredEncoding(TypedValue* rv, HPHP::VM::ActRec* ar, long long count, ObjectData* this_) __attribute__((noinline,cold));
TypedValue* tg1_16EncodingDetector_setDeclaredEncoding(TypedValue* rv, HPHP::VM::ActRec* ar, long long count, ObjectData* this_) {
  TypedValue* args UNUSED = ((TypedValue*)ar) - 1;
  rv->m_data.num = 0LL;
  rv->_count = 0;
  rv->m_type = KindOfNull;
  tvCastToStringInPlace(args-0);
  th_16EncodingDetector_setDeclaredEncoding((this_), (Value*)(args-0));
  return rv;
}

TypedValue* tg_16EncodingDetector_setDeclaredEncoding(HPHP::VM::ActRec *ar) {
  EXCEPTION_GATE_ENTER();
    TypedValue rv;
    long long count = ar->numArgs();
    TypedValue* args UNUSED = ((TypedValue*)ar) - 1;
    ObjectData* this_ = (ar->hasThis() ? ar->getThis() : NULL);
    if (this_) {
      if (count == 1LL) {
        if (IS_STRING_TYPE((args-0)->m_type)) {
          rv.m_data.num = 0LL;
          rv._count = 0;
          rv.m_type = KindOfNull;
          th_16EncodingDetector_setDeclaredEncoding((this_), (Value*)(args-0));
          frame_free_locals_inl(ar, 1);
          memcpy(&ar->m_r, &rv, sizeof(TypedValue));
          return &ar->m_r;
        } else {
          tg1_16EncodingDetector_setDeclaredEncoding(&rv, ar, count , this_);
          frame_free_locals_inl(ar, 1);
          memcpy(&ar->m_r, &rv, sizeof(TypedValue));
          return &ar->m_r;
        }
      } else {
        throw_wrong_arguments_nr("EncodingDetector::setDeclaredEncoding", count, 1, 1, 1);
      }
    } else {
      throw_instance_method_fatal("EncodingDetector::setDeclaredEncoding");
    }
    rv.m_data.num = 0LL;
    rv._count = 0;
    rv.m_type = KindOfNull;
    frame_free_locals_inl(ar, 1);
    memcpy(&ar->m_r, &rv, sizeof(TypedValue));
    return &ar->m_r;
  EXCEPTION_GATE_RETURN(&ar->m_r);
}

/*
HPHP::Object HPHP::c_EncodingDetector::t_detect()
_ZN4HPHP18c_EncodingDetector8t_detectEv

(return value) => rax
_rv => rdi
this_ => rsi
*/

Value* th_16EncodingDetector_detect(Value* _rv, ObjectData* this_) asm("_ZN4HPHP18c_EncodingDetector8t_detectEv");

TypedValue* tg_16EncodingDetector_detect(HPHP::VM::ActRec *ar) {
  EXCEPTION_GATE_ENTER();
    TypedValue rv;
    long long count = ar->numArgs();
    TypedValue* args UNUSED = ((TypedValue*)ar) - 1;
    ObjectData* this_ = (ar->hasThis() ? ar->getThis() : NULL);
    if (this_) {
      if (count == 0LL) {
        rv._count = 0;
        rv.m_type = KindOfObject;
        th_16EncodingDetector_detect((Value*)(&(rv)), (this_));
        if (rv.m_data.num == 0LL) rv.m_type = KindOfNull;
        frame_free_locals_inl(ar, 0);
        memcpy(&ar->m_r, &rv, sizeof(TypedValue));
        return &ar->m_r;
      } else {
        throw_toomany_arguments_nr("EncodingDetector::detect", 0, 1);
      }
    } else {
      throw_instance_method_fatal("EncodingDetector::detect");
    }
    rv.m_data.num = 0LL;
    rv._count = 0;
    rv.m_type = KindOfNull;
    frame_free_locals_inl(ar, 0);
    memcpy(&ar->m_r, &rv, sizeof(TypedValue));
    return &ar->m_r;
  EXCEPTION_GATE_RETURN(&ar->m_r);
}

/*
HPHP::Array HPHP::c_EncodingDetector::t_detectall()
_ZN4HPHP18c_EncodingDetector11t_detectallEv

(return value) => rax
_rv => rdi
this_ => rsi
*/

Value* th_16EncodingDetector_detectAll(Value* _rv, ObjectData* this_) asm("_ZN4HPHP18c_EncodingDetector11t_detectallEv");

TypedValue* tg_16EncodingDetector_detectAll(HPHP::VM::ActRec *ar) {
  EXCEPTION_GATE_ENTER();
    TypedValue rv;
    long long count = ar->numArgs();
    TypedValue* args UNUSED = ((TypedValue*)ar) - 1;
    ObjectData* this_ = (ar->hasThis() ? ar->getThis() : NULL);
    if (this_) {
      if (count == 0LL) {
        rv._count = 0;
        rv.m_type = KindOfArray;
        th_16EncodingDetector_detectAll((Value*)(&(rv)), (this_));
        if (rv.m_data.num == 0LL) rv.m_type = KindOfNull;
        frame_free_locals_inl(ar, 0);
        memcpy(&ar->m_r, &rv, sizeof(TypedValue));
        return &ar->m_r;
      } else {
        throw_toomany_arguments_nr("EncodingDetector::detectAll", 0, 1);
      }
    } else {
      throw_instance_method_fatal("EncodingDetector::detectAll");
    }
    rv.m_data.num = 0LL;
    rv._count = 0;
    rv.m_type = KindOfNull;
    frame_free_locals_inl(ar, 0);
    memcpy(&ar->m_r, &rv, sizeof(TypedValue));
    return &ar->m_r;
  EXCEPTION_GATE_RETURN(&ar->m_r);
}

/*
HPHP::Variant HPHP::c_EncodingDetector::t___destruct()
_ZN4HPHP18c_EncodingDetector12t___destructEv

(return value) => rax
_rv => rdi
this_ => rsi
*/

TypedValue* th_16EncodingDetector___destruct(TypedValue* _rv, ObjectData* this_) asm("_ZN4HPHP18c_EncodingDetector12t___destructEv");

TypedValue* tg_16EncodingDetector___destruct(HPHP::VM::ActRec *ar) {
  EXCEPTION_GATE_ENTER();
    TypedValue rv;
    long long count = ar->numArgs();
    TypedValue* args UNUSED = ((TypedValue*)ar) - 1;
    ObjectData* this_ = (ar->hasThis() ? ar->getThis() : NULL);
    if (this_) {
      if (count == 0LL) {
        th_16EncodingDetector___destruct((&(rv)), (this_));
        if (rv.m_type == KindOfUninit) rv.m_type = KindOfNull;
        frame_free_locals_inl(ar, 0);
        memcpy(&ar->m_r, &rv, sizeof(TypedValue));
        return &ar->m_r;
      } else {
        throw_toomany_arguments_nr("EncodingDetector::__destruct", 0, 1);
      }
    } else {
      throw_instance_method_fatal("EncodingDetector::__destruct");
    }
    rv.m_data.num = 0LL;
    rv._count = 0;
    rv.m_type = KindOfNull;
    frame_free_locals_inl(ar, 0);
    memcpy(&ar->m_r, &rv, sizeof(TypedValue));
    return &ar->m_r;
  EXCEPTION_GATE_RETURN(&ar->m_r);
}

class c_EncodingMatch_Instance : public c_EncodingMatch {
public:
  c_EncodingMatch_Instance (HPHP::VM::Class* cls, unsigned nProps) {
    DECLARE_STACK_GC_ROOT(ObjectData, this);
    m_cls = cls;
    setAttributes(cls->getODAttrs()
                  | (cls->clsInfo()
                     ? 0 : IsInstance));
    m_propVec = (TypedValue *)((uintptr_t)this + sizeof(c_EncodingMatch));
    if (cls->needInitialization()) {
      cls->initialize();
    }
    if (nProps > 0) {
      if (cls->pinitVec().size() > 0) {
        initialize(nProps);
      } else {
        ASSERT(nProps == cls->declPropInit().size());
        memcpy(m_propVec, &cls->declPropInit()[0], nProps * sizeof(TypedValue));
      }
    }
  }
  static HPHP::VM::Instance* new_Instance(HPHP::VM::Class* cls) {
    size_t nProps = cls->numDeclProperties();
    size_t builtinPropSize = sizeof(c_EncodingMatch) - sizeof(ObjectData);
    size_t size = sizeForNProps(nProps) + builtinPropSize;
    HPHP::VM::Instance *inst = (HPHP::VM::Instance*)ALLOCOBJSZ(size);
    new ((void *)inst) c_EncodingMatch_Instance(cls, nProps);
    return inst;
  }
  void operator delete(void *p) {
    c_EncodingMatch_Instance *this_ = (c_EncodingMatch_Instance*)p;
    size_t nProps = this_->m_cls->numDeclProperties();
    size_t builtinPropSize UNUSED = sizeof(c_EncodingMatch) - sizeof(ObjectData);
    if (this_->m_propMap) {
      this_->m_propMap->release();
    }
    for (size_t i = 0; i < nProps; ++i) {
      TypedValue *prop = &this_->m_propVec[i];
      tvRefcountedDecRef(prop);
    }
    DELETEOBJSZ(sizeForNProps(nProps) + builtinPropSize)(this_);
  }
  virtual bool o_instanceof(const HPHP::String& s) const {
    return Instance::o_instanceof(s) || c_EncodingMatch::o_instanceof(s);
  }
  virtual Variant* o_realProp(CStrRef s, int flags, CStrRef context) const {
    Variant *v = Instance::o_realProp(s, flags, context);
    if (v) return v;
    return c_EncodingMatch::o_realProp(s, flags, context);
  }
  virtual Variant* o_realPropPublic(CStrRef s, int flags) const {
    Variant *v = Instance::o_realPropPublic(s, flags);
    if (v) return v;
    return c_EncodingMatch::o_realPropPublic(s, flags);
  }
  virtual void o_setArray(CArrRef props) {
    ClassInfo::SetArray(this, o_getClassPropTable(), props);
  }
  virtual void o_getArray(Array &props, bool pubOnly) const {
    ClassInfo::GetArray(this, o_getClassPropTable(), props, false);
}
  virtual ObjectData* cloneImpl() {
    return Instance::cloneImpl();
  }
  virtual void cloneSet(ObjectData *clone) {
    c_EncodingMatch::cloneSet(clone);
    Instance::cloneSet(clone);
  }
};

HPHP::VM::Instance* new_EncodingMatch_Instance(HPHP::VM::Class* cls) {
  return c_EncodingMatch_Instance::new_Instance(cls);
}

/*
void HPHP::c_EncodingMatch::t___construct()
_ZN4HPHP15c_EncodingMatch13t___constructEv

this_ => rdi
*/

void th_13EncodingMatch___construct(ObjectData* this_) asm("_ZN4HPHP15c_EncodingMatch13t___constructEv");

TypedValue* tg_13EncodingMatch___construct(HPHP::VM::ActRec *ar) {
  EXCEPTION_GATE_ENTER();
    TypedValue rv;
    long long count = ar->numArgs();
    TypedValue* args UNUSED = ((TypedValue*)ar) - 1;
    ObjectData* this_ = (ar->hasThis() ? ar->getThis() : NULL);
    if (this_) {
      if (count == 0LL) {
        rv.m_data.num = 0LL;
        rv._count = 0;
        rv.m_type = KindOfNull;
        th_13EncodingMatch___construct((this_));
        frame_free_locals_inl(ar, 0);
        memcpy(&ar->m_r, &rv, sizeof(TypedValue));
        return &ar->m_r;
      } else {
        throw_toomany_arguments_nr("EncodingMatch::__construct", 0, 1);
      }
    } else {
      throw_instance_method_fatal("EncodingMatch::__construct");
    }
    rv.m_data.num = 0LL;
    rv._count = 0;
    rv.m_type = KindOfNull;
    frame_free_locals_inl(ar, 0);
    memcpy(&ar->m_r, &rv, sizeof(TypedValue));
    return &ar->m_r;
  EXCEPTION_GATE_RETURN(&ar->m_r);
}

/*
bool HPHP::c_EncodingMatch::t_isvalid()
_ZN4HPHP15c_EncodingMatch9t_isvalidEv

(return value) => rax
this_ => rdi
*/

bool th_13EncodingMatch_isValid(ObjectData* this_) asm("_ZN4HPHP15c_EncodingMatch9t_isvalidEv");

TypedValue* tg_13EncodingMatch_isValid(HPHP::VM::ActRec *ar) {
  EXCEPTION_GATE_ENTER();
    TypedValue rv;
    long long count = ar->numArgs();
    TypedValue* args UNUSED = ((TypedValue*)ar) - 1;
    ObjectData* this_ = (ar->hasThis() ? ar->getThis() : NULL);
    if (this_) {
      if (count == 0LL) {
        rv._count = 0;
        rv.m_type = KindOfBoolean;
        rv.m_data.num = (th_13EncodingMatch_isValid((this_))) ? 1LL : 0LL;
        frame_free_locals_inl(ar, 0);
        memcpy(&ar->m_r, &rv, sizeof(TypedValue));
        return &ar->m_r;
      } else {
        throw_toomany_arguments_nr("EncodingMatch::isValid", 0, 1);
      }
    } else {
      throw_instance_method_fatal("EncodingMatch::isValid");
    }
    rv.m_data.num = 0LL;
    rv._count = 0;
    rv.m_type = KindOfNull;
    frame_free_locals_inl(ar, 0);
    memcpy(&ar->m_r, &rv, sizeof(TypedValue));
    return &ar->m_r;
  EXCEPTION_GATE_RETURN(&ar->m_r);
}

/*
HPHP::String HPHP::c_EncodingMatch::t_getencoding()
_ZN4HPHP15c_EncodingMatch13t_getencodingEv

(return value) => rax
_rv => rdi
this_ => rsi
*/

Value* th_13EncodingMatch_getEncoding(Value* _rv, ObjectData* this_) asm("_ZN4HPHP15c_EncodingMatch13t_getencodingEv");

TypedValue* tg_13EncodingMatch_getEncoding(HPHP::VM::ActRec *ar) {
  EXCEPTION_GATE_ENTER();
    TypedValue rv;
    long long count = ar->numArgs();
    TypedValue* args UNUSED = ((TypedValue*)ar) - 1;
    ObjectData* this_ = (ar->hasThis() ? ar->getThis() : NULL);
    if (this_) {
      if (count == 0LL) {
        rv._count = 0;
        rv.m_type = KindOfString;
        th_13EncodingMatch_getEncoding((Value*)(&(rv)), (this_));
        if (rv.m_data.num == 0LL) rv.m_type = KindOfNull;
        frame_free_locals_inl(ar, 0);
        memcpy(&ar->m_r, &rv, sizeof(TypedValue));
        return &ar->m_r;
      } else {
        throw_toomany_arguments_nr("EncodingMatch::getEncoding", 0, 1);
      }
    } else {
      throw_instance_method_fatal("EncodingMatch::getEncoding");
    }
    rv.m_data.num = 0LL;
    rv._count = 0;
    rv.m_type = KindOfNull;
    frame_free_locals_inl(ar, 0);
    memcpy(&ar->m_r, &rv, sizeof(TypedValue));
    return &ar->m_r;
  EXCEPTION_GATE_RETURN(&ar->m_r);
}

/*
int HPHP::c_EncodingMatch::t_getconfidence()
_ZN4HPHP15c_EncodingMatch15t_getconfidenceEv

(return value) => rax
this_ => rdi
*/

int th_13EncodingMatch_getConfidence(ObjectData* this_) asm("_ZN4HPHP15c_EncodingMatch15t_getconfidenceEv");

TypedValue* tg_13EncodingMatch_getConfidence(HPHP::VM::ActRec *ar) {
  EXCEPTION_GATE_ENTER();
    TypedValue rv;
    long long count = ar->numArgs();
    TypedValue* args UNUSED = ((TypedValue*)ar) - 1;
    ObjectData* this_ = (ar->hasThis() ? ar->getThis() : NULL);
    if (this_) {
      if (count == 0LL) {
        rv._count = 0;
        rv.m_type = KindOfInt64;
        rv.m_data.num = (long long)th_13EncodingMatch_getConfidence((this_));
        frame_free_locals_inl(ar, 0);
        memcpy(&ar->m_r, &rv, sizeof(TypedValue));
        return &ar->m_r;
      } else {
        throw_toomany_arguments_nr("EncodingMatch::getConfidence", 0, 1);
      }
    } else {
      throw_instance_method_fatal("EncodingMatch::getConfidence");
    }
    rv.m_data.num = 0LL;
    rv._count = 0;
    rv.m_type = KindOfNull;
    frame_free_locals_inl(ar, 0);
    memcpy(&ar->m_r, &rv, sizeof(TypedValue));
    return &ar->m_r;
  EXCEPTION_GATE_RETURN(&ar->m_r);
}

/*
HPHP::String HPHP::c_EncodingMatch::t_getlanguage()
_ZN4HPHP15c_EncodingMatch13t_getlanguageEv

(return value) => rax
_rv => rdi
this_ => rsi
*/

Value* th_13EncodingMatch_getLanguage(Value* _rv, ObjectData* this_) asm("_ZN4HPHP15c_EncodingMatch13t_getlanguageEv");

TypedValue* tg_13EncodingMatch_getLanguage(HPHP::VM::ActRec *ar) {
  EXCEPTION_GATE_ENTER();
    TypedValue rv;
    long long count = ar->numArgs();
    TypedValue* args UNUSED = ((TypedValue*)ar) - 1;
    ObjectData* this_ = (ar->hasThis() ? ar->getThis() : NULL);
    if (this_) {
      if (count == 0LL) {
        rv._count = 0;
        rv.m_type = KindOfString;
        th_13EncodingMatch_getLanguage((Value*)(&(rv)), (this_));
        if (rv.m_data.num == 0LL) rv.m_type = KindOfNull;
        frame_free_locals_inl(ar, 0);
        memcpy(&ar->m_r, &rv, sizeof(TypedValue));
        return &ar->m_r;
      } else {
        throw_toomany_arguments_nr("EncodingMatch::getLanguage", 0, 1);
      }
    } else {
      throw_instance_method_fatal("EncodingMatch::getLanguage");
    }
    rv.m_data.num = 0LL;
    rv._count = 0;
    rv.m_type = KindOfNull;
    frame_free_locals_inl(ar, 0);
    memcpy(&ar->m_r, &rv, sizeof(TypedValue));
    return &ar->m_r;
  EXCEPTION_GATE_RETURN(&ar->m_r);
}

/*
HPHP::String HPHP::c_EncodingMatch::t_getutf8()
_ZN4HPHP15c_EncodingMatch9t_getutf8Ev

(return value) => rax
_rv => rdi
this_ => rsi
*/

Value* th_13EncodingMatch_getUTF8(Value* _rv, ObjectData* this_) asm("_ZN4HPHP15c_EncodingMatch9t_getutf8Ev");

TypedValue* tg_13EncodingMatch_getUTF8(HPHP::VM::ActRec *ar) {
  EXCEPTION_GATE_ENTER();
    TypedValue rv;
    long long count = ar->numArgs();
    TypedValue* args UNUSED = ((TypedValue*)ar) - 1;
    ObjectData* this_ = (ar->hasThis() ? ar->getThis() : NULL);
    if (this_) {
      if (count == 0LL) {
        rv._count = 0;
        rv.m_type = KindOfString;
        th_13EncodingMatch_getUTF8((Value*)(&(rv)), (this_));
        if (rv.m_data.num == 0LL) rv.m_type = KindOfNull;
        frame_free_locals_inl(ar, 0);
        memcpy(&ar->m_r, &rv, sizeof(TypedValue));
        return &ar->m_r;
      } else {
        throw_toomany_arguments_nr("EncodingMatch::getUTF8", 0, 1);
      }
    } else {
      throw_instance_method_fatal("EncodingMatch::getUTF8");
    }
    rv.m_data.num = 0LL;
    rv._count = 0;
    rv.m_type = KindOfNull;
    frame_free_locals_inl(ar, 0);
    memcpy(&ar->m_r, &rv, sizeof(TypedValue));
    return &ar->m_r;
  EXCEPTION_GATE_RETURN(&ar->m_r);
}

/*
HPHP::Variant HPHP::c_EncodingMatch::t___destruct()
_ZN4HPHP15c_EncodingMatch12t___destructEv

(return value) => rax
_rv => rdi
this_ => rsi
*/

TypedValue* th_13EncodingMatch___destruct(TypedValue* _rv, ObjectData* this_) asm("_ZN4HPHP15c_EncodingMatch12t___destructEv");

TypedValue* tg_13EncodingMatch___destruct(HPHP::VM::ActRec *ar) {
  EXCEPTION_GATE_ENTER();
    TypedValue rv;
    long long count = ar->numArgs();
    TypedValue* args UNUSED = ((TypedValue*)ar) - 1;
    ObjectData* this_ = (ar->hasThis() ? ar->getThis() : NULL);
    if (this_) {
      if (count == 0LL) {
        th_13EncodingMatch___destruct((&(rv)), (this_));
        if (rv.m_type == KindOfUninit) rv.m_type = KindOfNull;
        frame_free_locals_inl(ar, 0);
        memcpy(&ar->m_r, &rv, sizeof(TypedValue));
        return &ar->m_r;
      } else {
        throw_toomany_arguments_nr("EncodingMatch::__destruct", 0, 1);
      }
    } else {
      throw_instance_method_fatal("EncodingMatch::__destruct");
    }
    rv.m_data.num = 0LL;
    rv._count = 0;
    rv.m_type = KindOfNull;
    frame_free_locals_inl(ar, 0);
    memcpy(&ar->m_r, &rv, sizeof(TypedValue));
    return &ar->m_r;
  EXCEPTION_GATE_RETURN(&ar->m_r);
}


} // !HPHP
