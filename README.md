# CString

### `std::string` Methods Covered/To Cover

- [X] Constructor > `CStringCreate`
- [X] Destructor > `CStringDestroy`
- [X] `std::string::operator=` > `CStringEqual`
- [X] `std::string::at` > `CStringAt`
- [X] `std::string::length` > `CStringLength`
- [X] `std::string::size` > `CStringSize`
- [X] `std::string::capacity` > `CStringCapacity`
- [X] `std::string::data` > `CStringData`
- [X] `std::string::empty` > `CStringEmpty`
- [X] `std::string::begin` > `CStringBegin`
- [X] `std::string::end` > `CStringEnd`
- [X] `std::string::rbegin` > `CStringRBegin`
- [X] `std::string::rend` > `CStringREnd`
- [X] `std::string::front` > `CStringFront`
- [X] `std::string::back` > `CStringBack`
- [ ] `std::string::max_size` > `CStringMaxSize`
- [ ] `std::string::reserve` > `CStringReserve`
- [ ] `std::string::shrink_to_fit` > `CStringShrinkToFit`
- [ ] `std::string::insert` > `CStringInsert`
- [ ] `std::string::erase` > `CStringErase`
- [ ] `std::string::push_back` > `CStringPushBack`
- [ ] `std::string::pop_back` > `CStringPopBack`
- [ ] `std::string::append` > `CStringAppend`
- [ ] `std::string::compare` > `CStringCompare`
- [ ] `std::string::starts_with` > `CStringStartsWith`
- [ ] `std::string::ends_with` > `CStringEndsWith`
- [ ] `std::string::replace` > `CStringReplace`
- [ ] `std::string::substr` > `CStringSubStr`
- [ ] `std::string::copy` > `CStringCopy`
- [ ] `std::string::resize` > `CStringResize`
- [ ] `std::string::swap` > `CStringSwap`
- [ ] `std::string::find` > `CStringFind`
- [ ] `std::string::rfind` > `CStringRFind`
- [ ] `std::string::find_first_of` > `CStringFindFirstOf`
- [ ] `std::string::find_first_not_of` > `CStringFindFirstNotOf`
- [ ] `std::string::find_last_of` > `CStringFindLastOf`
- [ ] `std::string::find_last_not_of` > `CStringFindLastNotOf`

__Note__: Except for `std::string::operator=`, which can be written in C as `CStringEqual`, other operators are not worth it to be written or can be achieved with already defined functions.