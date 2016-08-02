//          Copyright Marc Bodmer 2016-2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cstdint>

namespace std {

    /**
     * Implementation of TR18015:2006 Chapter 8
     * Intended usage on Microcontrollers.
     * This header is self containing and definitions from iohw.h are
     * not used. If needed they are defined here.
     */
    namespace hardware {

struct hw_base {
  typedef ::ioreg_t address_type;
  enum access_mode { random, read, read_write, write };
  enum device_bus { device8, device16, device32, device64 };
  enum byte_order { msb_low, msb_high };
  enum processor_bus { bus8, bus16, bus32, bus64 };
  enum data_bus {  };
  enum io_bus { i2c, spi };
  enum address_kind { is_static, is_dynamic };
};

template<hw_base::address_type val>
struct static_address {
  enum { value_ = val };
  hw_base::address_type value() const { return (val); }
};

struct dynamic_address {
  dynamic_address(hw_base::address_type address) : value_(address) { }
  hw_base::address_type value() const { return (value_); }
  hw_base::address_type value_;
};

struct platform_traits {
  typedef hw_base::address_type address_holder;
  typedef hw_base::io_bus processor_bus;
  enum { address_mode, processor_endianness, processor_bus_width };
};

struct register_traits {
  typedef unsigned int value_type;
  typedef hw_base::address_type address_holder;
  enum { address_mode=hw_base, access_mode, endianness, device_bus_width };
};

/**
 * Provides direct access to hardware registers.
 * This defines the interface for the top layer as described in tr18015 8.1.4
 *
 * @RegisterTraits
 * The argument to the first template parameter RegisterTraits must be a class or
 * instantiation of a class template that is a derived class of register_traits and
 * specify the register-specific access properties of the hardware register.
 *
 * @PlatformTraits
 * The argument to the second template parameter PlatformTraits must be a
 * class or instantiation of a class template that is a derived class of
 * platform_traits and specify the platform-specific access properties of the
 * hardware register.
 */
template<
  class RegisterTraits = register_traits,
  class PlatformTraits = platform_traits>
class register_access {
public:

  /** Names the value_type of the RegTraits */
  typedef typename RegisterTraits::value_type value_type;

  /*
   * Default Constructor. If an address holder is marked as is_static in
   * its traits class, the respective constructor argument shall not be given.
   */
  register_access();

  /*
   * The Constructor takes a reference to the address_holder class
   * of the RegisterTraits template parameter. If an address holder is marked
   * as is_static in its traits class, the respective constructor argument
   * shall not be given.
   */
  explicit register_access(
    typename RegisterTraits::address_holder const &reg_traits_addr);

  /*
   * The Constructor takes a reference to the address_holder class
   * of the PlatformTraits template parameter. If an address holder is marked
   * as is_static in its traits class, the respective constructor argument
   * shall not be given.
   */
  explicit register_access(
    typename PlatformTraits::address_holder const &pf_traits_addr);

  /*
   * The Constructor takes references to the respective address_holder classes
   * of the access specification traits template parameters.
   */
  register_access(
    typename RegisterTraits::address_holder const &reg_traits_addr,
    typename PlatformTraits::address_holder const &pf_traits_addr);

  operator value_type() const;


  void operator=(value_type val);
  void operator|=(value_type val);
  void operator&=(value_type val);
  void operator^=(value_type val);

  /**
  * Provides read access to the hardware register.
  */
  value_type read() const;

  /**
   * Writes the value_type argument val to the hardware register.
   */
  void write(value_type val);

  void or_with(value_type val);
  void and_with(value_type val);
  void xor_with(value_type val);
};

template<
  class RegisterTraits = register_traits,
  class PlatformTraits = platform_traits>
class register_buffer {
public:
  typedef register_access<RegisterTraits, PlatformTraits> ref_type;
  typedef typename RegisterTraits::value_type value_type;

  register_buffer(
    typename RegisterTraits::address_holder const &rAddr,
    typename PlatformTraits::address_holder const &pAddr);
  register_buffer(
    typename PlatformTraits::address_holder const &pAddr);
  register_buffer();

  ref_type operator[](::ioindex_t idx) const;

  ref_type get_buffer_element(::ioindex_t idx) const;
};

}} // ::std::hardware
