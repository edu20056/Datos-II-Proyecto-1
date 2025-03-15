// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: proto/hello.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_proto_2fhello_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_proto_2fhello_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION < 4023000
#error "This file was generated by a newer version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please update"
#error "your headers."
#endif  // PROTOBUF_VERSION

#if 4023001 < PROTOBUF_MIN_PROTOC_VERSION
#error "This file was generated by an older version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please"
#error "regenerate this file with a newer version of protoc."
#endif  // PROTOBUF_MIN_PROTOC_VERSION
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_proto_2fhello_2eproto

PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_proto_2fhello_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable
    descriptor_table_proto_2fhello_2eproto;
class Numeric;
struct NumericDefaultTypeInternal;
extern NumericDefaultTypeInternal _Numeric_default_instance_;
class Point3;
struct Point3DefaultTypeInternal;
extern Point3DefaultTypeInternal _Point3_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template <>
::Numeric* Arena::CreateMaybeMessage<::Numeric>(Arena*);
template <>
::Point3* Arena::CreateMaybeMessage<::Point3>(Arena*);
PROTOBUF_NAMESPACE_CLOSE


// ===================================================================


// -------------------------------------------------------------------

class Point3 final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Point3) */ {
 public:
  inline Point3() : Point3(nullptr) {}
  ~Point3() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR Point3(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Point3(const Point3& from);
  Point3(Point3&& from) noexcept
    : Point3() {
    *this = ::std::move(from);
  }

  inline Point3& operator=(const Point3& from) {
    CopyFrom(from);
    return *this;
  }
  inline Point3& operator=(Point3&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Point3& default_instance() {
    return *internal_default_instance();
  }
  static inline const Point3* internal_default_instance() {
    return reinterpret_cast<const Point3*>(
               &_Point3_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Point3& a, Point3& b) {
    a.Swap(&b);
  }
  inline void Swap(Point3* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Point3* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Point3* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Point3>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Point3& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const Point3& from) {
    Point3::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Point3* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "Point3";
  }
  protected:
  explicit Point3(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kXFieldNumber = 1,
    kYFieldNumber = 2,
    kZFieldNumber = 3,
  };
  // float x = 1;
  void clear_x() ;
  float x() const;
  void set_x(float value);

  private:
  float _internal_x() const;
  void _internal_set_x(float value);

  public:
  // float y = 2;
  void clear_y() ;
  float y() const;
  void set_y(float value);

  private:
  float _internal_y() const;
  void _internal_set_y(float value);

  public:
  // float z = 3;
  void clear_z() ;
  float z() const;
  void set_z(float value);

  private:
  float _internal_z() const;
  void _internal_set_z(float value);

  public:
  // @@protoc_insertion_point(class_scope:Point3)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    float x_;
    float y_;
    float z_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_proto_2fhello_2eproto;
};// -------------------------------------------------------------------

class Numeric final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Numeric) */ {
 public:
  inline Numeric() : Numeric(nullptr) {}
  ~Numeric() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR Numeric(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Numeric(const Numeric& from);
  Numeric(Numeric&& from) noexcept
    : Numeric() {
    *this = ::std::move(from);
  }

  inline Numeric& operator=(const Numeric& from) {
    CopyFrom(from);
    return *this;
  }
  inline Numeric& operator=(Numeric&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Numeric& default_instance() {
    return *internal_default_instance();
  }
  static inline const Numeric* internal_default_instance() {
    return reinterpret_cast<const Numeric*>(
               &_Numeric_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Numeric& a, Numeric& b) {
    a.Swap(&b);
  }
  inline void Swap(Numeric* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Numeric* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Numeric* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Numeric>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Numeric& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const Numeric& from) {
    Numeric::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Numeric* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "Numeric";
  }
  protected:
  explicit Numeric(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kValueFieldNumber = 1,
  };
  // float value = 1;
  void clear_value() ;
  float value() const;
  void set_value(float value);

  private:
  float _internal_value() const;
  void _internal_set_value(float value);

  public:
  // @@protoc_insertion_point(class_scope:Numeric)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    float value_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_proto_2fhello_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// Point3

// float x = 1;
inline void Point3::clear_x() {
  _impl_.x_ = 0;
}
inline float Point3::x() const {
  // @@protoc_insertion_point(field_get:Point3.x)
  return _internal_x();
}
inline void Point3::set_x(float value) {
  _internal_set_x(value);
  // @@protoc_insertion_point(field_set:Point3.x)
}
inline float Point3::_internal_x() const {
  return _impl_.x_;
}
inline void Point3::_internal_set_x(float value) {
  ;
  _impl_.x_ = value;
}

// float y = 2;
inline void Point3::clear_y() {
  _impl_.y_ = 0;
}
inline float Point3::y() const {
  // @@protoc_insertion_point(field_get:Point3.y)
  return _internal_y();
}
inline void Point3::set_y(float value) {
  _internal_set_y(value);
  // @@protoc_insertion_point(field_set:Point3.y)
}
inline float Point3::_internal_y() const {
  return _impl_.y_;
}
inline void Point3::_internal_set_y(float value) {
  ;
  _impl_.y_ = value;
}

// float z = 3;
inline void Point3::clear_z() {
  _impl_.z_ = 0;
}
inline float Point3::z() const {
  // @@protoc_insertion_point(field_get:Point3.z)
  return _internal_z();
}
inline void Point3::set_z(float value) {
  _internal_set_z(value);
  // @@protoc_insertion_point(field_set:Point3.z)
}
inline float Point3::_internal_z() const {
  return _impl_.z_;
}
inline void Point3::_internal_set_z(float value) {
  ;
  _impl_.z_ = value;
}

// -------------------------------------------------------------------

// Numeric

// float value = 1;
inline void Numeric::clear_value() {
  _impl_.value_ = 0;
}
inline float Numeric::value() const {
  // @@protoc_insertion_point(field_get:Numeric.value)
  return _internal_value();
}
inline void Numeric::set_value(float value) {
  _internal_set_value(value);
  // @@protoc_insertion_point(field_set:Numeric.value)
}
inline float Numeric::_internal_value() const {
  return _impl_.value_;
}
inline void Numeric::_internal_set_value(float value) {
  ;
  _impl_.value_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_proto_2fhello_2eproto_2epb_2eh
