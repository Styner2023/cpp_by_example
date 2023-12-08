﻿/* NOT PRODUCTION QUALITY CODE, just shows learning/teaching example, not real programming, don't copy this style, just playing around
Copyright Grant Rostig 2015 - 2021. Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
Author: 		Grant Rostig
Inspired by:
-Generated as part of Grant's password manager effort to show how the Overloaded pattern is used by std::visit.

Shows how:
- The menu system allows for various function signatures and various configurations of return values.
- The overloaded type and std::visit can be applied to a menu multi-level system.

Reminder of usefull resources:
https://coliru.stacked-crooked.com/
https://godbolt.org/
https://cppinsights.io/
https://Wandbox.org
https://arnemertz.github.io/online-compilers/
Note: UDTs have initial capitalization. */
#include <bits/stdc++.h>
using std::cout, std::cin, std::cerr, std::endl;

template<class... Ts> struct Overloaded : Ts... {	using Ts::operator()...; };
template<class... Ts> Overloaded(Ts...) -> Overloaded<Ts...>;  // deduction guide.  -> = returns.  TODO??: explain: what returns what to whom?

struct Menu_state {     // State VARs of the menu system, this would contain the stack of menus and submenus, of the current context. The details are ommitted here to focus our questions.
    int 	    my_int 	    {990};
    std::string my_string 	{"NULL_STRING"};
};

/// Informs the menu system what to do after an "action" has been completed.
/// An "action" is the function that the menu system "runs"/invokes/calls/executes??.
/// We study both the cases where: 1) the return value consists of one variable; 2) it consists of two variables.
enum class Functions_menu_intent {   retain_menu, prior_menu, terminate };

/// After running a "menu action", the return type consisting of 1 value
struct Action_return_1value {
    Functions_menu_intent   fns_menu_intent{Functions_menu_intent::terminate};
};
/// After running a "menu action", the return type consisting of 2 values
struct Action_return_2values {
    Functions_menu_intent   fns_menu_intent{Functions_menu_intent::retain_menu};
    std::string             my_string{};
};
/// A menu action could return different numbers and types of return values.
/// Unfortunately not part of the function signature, and not used by std::visit for visit function differentiation.
using Action_return_value_variant =
        std::variant <
            //std::monostate,  	    // OR					// TODO??: good idea?
            Action_return_1value ,  // OR
            Action_return_2values
        >;

/** Vary the return signature (*_signature1_?) between a variety parameter types,
    and also number of parameters, useful for study examples,
    while keeping the return type the same, it being "1value".
    Note: I'm here I'm considering the signature to include the return type, which is not how C++ defines it? todo?: */
using Menu_action_1value_signature_1 = Action_return_1value( int& );  // Note: the use of the meaning of the term 'signature' is expanded to includes the return type.
using Menu_action_1value_signature_2 = Action_return_1value( double& );
using Menu_action_1value_signature_3 = Action_return_1value( int&, std::string &);
using Menu_action_1value_signature_4 = Action_return_1value( Menu_state &, int& );
using Menu_action_1value_signature_5 = Action_return_1value( Menu_state &, double& );
using Menu_action_1value_signature_6 = Action_return_1value( Menu_state &, int&, std::string &);
using Menu_action_1value_signature_7 = Action_return_1value( Menu_state &, int&, int&, std::string &);
/// specify the std::functions to hold the above variations of FN signature&return.
using Menu_action_1value_ret_fn_1 = std::function< Menu_action_1value_signature_1>;
using Menu_action_1value_ret_fn_2 = std::function< Menu_action_1value_signature_2>;
using Menu_action_1value_ret_fn_3 = std::function< Menu_action_1value_signature_3>;
using Menu_action_1value_ret_fn_4 = std::function< Menu_action_1value_signature_4>;
using Menu_action_1value_ret_fn_5 = std::function< Menu_action_1value_signature_5>;
using Menu_action_1value_ret_fn_6 = std::function< Menu_action_1value_signature_6>;
using Menu_action_1value_ret_fn_7 = std::function< Menu_action_1value_signature_7>;

/// Allow for a compound return type, it being "2values".
using Menu_action_2value_signature_1 = Action_return_2values( int& );
using Menu_action_2value_signature_2 = Action_return_2values( double& );
using Menu_action_2value_signature_3 = Action_return_2values( int&, std::string &);
using Menu_action_2value_signature_4 = Action_return_2values( Menu_state &, int&);
using Menu_action_2value_signature_5 = Action_return_2values( Menu_state &, double&);
using Menu_action_2value_signature_6 = Action_return_2values( Menu_state &, int&, std::string &);
using Menu_action_2value_signature_7 = Action_return_2values( Menu_state &, int&, int&, std::string &);
/// specify std::functions to hold the above variations of FN signature&return.
using Menu_action_2values_ret_fn_1 = std::function< Menu_action_2value_signature_1>;
using Menu_action_2values_ret_fn_2 = std::function< Menu_action_2value_signature_2>;
using Menu_action_2values_ret_fn_3 = std::function< Menu_action_2value_signature_3>;
using Menu_action_2values_ret_fn_4 = std::function< Menu_action_2value_signature_4>;
using Menu_action_2values_ret_fn_5 = std::function< Menu_action_2value_signature_5>;
using Menu_action_2values_ret_fn_6 = std::function< Menu_action_2value_signature_6>;
using Menu_action_2values_ret_fn_7 = std::function< Menu_action_2value_signature_7>;

/// Menu actions can have all of the above combinations of signature&returns.
struct Menu_action {
    std::string name { "Init'ed menu action name." };
    std::variant< Menu_action_1value_ret_fn_1,
                  Menu_action_1value_ret_fn_2,
                  Menu_action_1value_ret_fn_3,
                  Menu_action_1value_ret_fn_4,
                  Menu_action_1value_ret_fn_5,
                  Menu_action_1value_ret_fn_6,
                  Menu_action_1value_ret_fn_7,

                  Menu_action_2values_ret_fn_1,
                  Menu_action_2values_ret_fn_2,
                  Menu_action_2values_ret_fn_3,
                  Menu_action_2values_ret_fn_4,
                  Menu_action_2values_ret_fn_5,
                  Menu_action_2values_ret_fn_6
    > action_fn_variant;
};

struct Menu {
    std::string 				name { "init'ed menu name."};
    std::vector< Menu_action > 	action {};
};

/** The various action functions invoked on running a Menu action.
    The return values are also varied for testing purposes. */
Action_return_1value action1_1( int & i) {
    cout << "action_int				 :"<<i<<endl; i++;
    return Action_return_1value{Functions_menu_intent::prior_menu};
}
Action_return_1value action1_2( double&  i) {
    cout << "action double			 :"<<i<<endl; i++;
    return Action_return_1value{Functions_menu_intent::terminate};
}
Action_return_1value action1_3( int&  i, std::string&  sval) {
    cout << "action_int_string		 :"<<i<<", "<<sval<<endl; i++;
    return Action_return_1value{Functions_menu_intent::retain_menu};
}
Action_return_1value action1_4(Menu_state & s, int&  i) {
    cout << "action_state_int		 :"<<s.my_int<<i<<endl; i++;
    return Action_return_1value{Functions_menu_intent::prior_menu};
}
Action_return_1value action1_5(Menu_state & s, double&  i) {
    cout << "action_state_double	 :"<<s.my_int<<", "<<i<<endl; i++;
    return Action_return_1value{Functions_menu_intent::terminate};
}
Action_return_1value action1_6(Menu_state & s, int &  i, std::string&  sval) {
    cout << "action_state_int_string :"<<s.my_int<<", "<<i<<", "<<sval<<endl; i++;
    return Action_return_1value{Functions_menu_intent::retain_menu};
}
Action_return_1value action1_7(Menu_state & s, int &  i, int & i2, std::string&  sval) {
    cout << "action_state_2int_string:"<<s.my_int<<", "<<i<<", "<<i2<<", "<<sval<<endl; i++;
    return Action_return_1value{Functions_menu_intent::retain_menu};
}

Action_return_2values action2_1( int&  i) {
    cout << "action_int2			 :"<<i<<endl; i++;
    return Action_return_2values{Functions_menu_intent::prior_menu, "1"};
}
Action_return_2values action2_2( double&  i) {
    cout << "action double2			 :"<<i<<endl; i++;
    return Action_return_2values{Functions_menu_intent::prior_menu, "2"};
}
Action_return_2values action2_3( int&  i, std::string& sval) {
    cout << "action_int_string2		 :"<<i<<", "<<sval<<endl; i++;
    return Action_return_2values{Functions_menu_intent::prior_menu, "3"};
}
Action_return_2values action2_4(Menu_state & s, int& i) {
    cout << "action_state_int2		 :"<<s.my_int<<", "<<i<<endl; i++;
    return Action_return_2values{Functions_menu_intent::prior_menu, "4"};
}
Action_return_2values action2_5(Menu_state & s, double& i) {
    cout << "action_state_double2    :"<<s.my_int<<", "<<i<<endl; i++;
    return Action_return_2values{Functions_menu_intent::prior_menu, "5"};
}
Action_return_2values action2_6(Menu_state & s, int & i, std::string& sval) {
    cout << "action_state_int_string2:"<<s.my_int<<", "<<i<<", "<<sval<<endl; i++;
    return Action_return_2values{Functions_menu_intent::prior_menu, "6"};
}
Action_return_2values action2_7(Menu_state & s, int & i, int & i2, std::string& sval) {
    cout << "action_state_2int_string2:"<<s.my_int<<", "<<i<<", "<<i2<<", "<<sval<<endl; i++;
    return Action_return_2values{Functions_menu_intent::prior_menu, "7"};
}

Action_return_value_variant call_menu_option_ifs( Menu_action const & menu_option, Menu_state & menu_state, int & ival, int & ival2, double &  dval, std::string &  sval ) {  // some of these are const because they will not change.
    if (       std::holds_alternative< Menu_action_1value_ret_fn_1 >( menu_option.action_fn_variant)) {  // NOTE: should have used std::get_if<> !!
        auto af = std::get< Menu_action_1value_ret_fn_1 >( menu_option.action_fn_variant);
        //auto af = constexpr if can be used here ....< Menu_action_1value_ret_fn >( m_opt.action_fn_variant);
        return af( ival );
    } else if (std::holds_alternative< Menu_action_1value_ret_fn_2 >( menu_option.action_fn_variant)) {
        auto af = std::get< Menu_action_1value_ret_fn_2 >( menu_option.action_fn_variant);
        return af( dval );
    } else if (std::holds_alternative< Menu_action_1value_ret_fn_3 >( menu_option.action_fn_variant)) {
        auto af = std::get< Menu_action_1value_ret_fn_3 >( menu_option.action_fn_variant);
        return af( ival, sval );
    } else if (std::holds_alternative< Menu_action_1value_ret_fn_4 >( menu_option.action_fn_variant)) {
        auto af = std::get< Menu_action_1value_ret_fn_4 >( menu_option.action_fn_variant);
        return af( menu_state, ival );
    } else if (std::holds_alternative< Menu_action_1value_ret_fn_5 >( menu_option.action_fn_variant)) {
        auto af = std::get< Menu_action_1value_ret_fn_5 >( menu_option.action_fn_variant);
        return af( menu_state, dval );
    } else if (std::holds_alternative< Menu_action_1value_ret_fn_6 >( menu_option.action_fn_variant)) {
        auto af = std::get< Menu_action_1value_ret_fn_6 >( menu_option.action_fn_variant);
        return af( menu_state, ival, sval );
    } else if (std::holds_alternative< Menu_action_1value_ret_fn_7 >( menu_option.action_fn_variant)) {
        auto af = std::get< Menu_action_1value_ret_fn_7 >( menu_option.action_fn_variant);
        return af( menu_state, ival, ival2, sval );
    }
    // 2 values return type
      else if (std::holds_alternative< Menu_action_2values_ret_fn_1 >( menu_option.action_fn_variant)) {
        auto af = std::get< Menu_action_2values_ret_fn_1 >( menu_option.action_fn_variant);
        return af( ival );
    } else if (std::holds_alternative< Menu_action_2values_ret_fn_2 >( menu_option.action_fn_variant)) {
        auto af = std::get< Menu_action_2values_ret_fn_2 >( menu_option.action_fn_variant);
        return af( dval );
    } else if (std::holds_alternative< Menu_action_2values_ret_fn_3 >( menu_option.action_fn_variant)) {
        auto af = std::get< Menu_action_2values_ret_fn_3 >( menu_option.action_fn_variant);
        return af( ival, sval );
    } else if (std::holds_alternative< Menu_action_2values_ret_fn_4 >( menu_option.action_fn_variant)) {
        auto af = std::get< Menu_action_2values_ret_fn_4 >( menu_option.action_fn_variant);
        return af( menu_state, ival );
    } else if (std::holds_alternative< Menu_action_2values_ret_fn_5 >( menu_option.action_fn_variant)) {
        auto af = std::get< Menu_action_2values_ret_fn_5 >( menu_option.action_fn_variant);
        return af( menu_state, dval );
    } else if (std::holds_alternative< Menu_action_2values_ret_fn_6 >( menu_option.action_fn_variant)) {
        auto af = std::get< Menu_action_2values_ret_fn_6 >( menu_option.action_fn_variant);
        return af( menu_state, ival, sval );
    //} else if (std::holds_alternative< Menu_action_2values_ret_fn_7 >( menu_option.action_fn_variant)) {  // TODO?: two int's are not allowed
        //auto af = std::get< Menu_action_2values_ret_fn_7 >( menu_option.action_fn_variant);
        //return af( menu_state, ival, ival2, sval );
    }
    else assert( false && ":didn't check all alternatives");
}

Action_return_value_variant call_menu_option_no_visit_1valret( Menu_action const & menu_option, Menu_state & menu_state, int & ival, int & ival2, double &  dval, std::string &  sval ) {  // some of these are const because they will not change.
    auto function_object_overload_set = Overloaded { // Note: Notice that the ival and dval are captured by reference even though the signatures of the functions are capture by value.
        //       This requirement is inconsistent with the above example/ugly code. todo: TODO does this cause indefined behavior?
        // duplicates make it ambigious [&ival]            (Menu_action_1value_ret_fn &af)  { Action_return_1 r = af(ival); return r; }, // to be invoked via operator() on the function object (AKA lambda) or any callable object.
        [&ival]            		(Menu_action_1value_ret_fn_1 const &af) ->Action_return_1value { Action_return_1value r = af(ival); return r; }, // to be invoked via operator() on the function object (AKA lambda) or any callable object.
        [&dval]            		(Menu_action_1value_ret_fn_2 const &af) ->Action_return_1value { Action_return_1value r = af(dval); return r; },
        [&ival,&sval]      		(Menu_action_1value_ret_fn_3 const &af) ->Action_return_1value { Action_return_1value r = af(ival,sval); return r; },
        [&menu_state,&ival]     (Menu_action_1value_ret_fn_4 const &af) ->Action_return_1value { Action_return_1value r = af(menu_state,ival); return r; },
        [&menu_state,&dval]     (Menu_action_1value_ret_fn_5 const &af) ->Action_return_1value { Action_return_1value r = af(menu_state,dval); return r; },
        //[&menu_state,&ival,&sval](Menu_action_1value_ret_fn_6 const &af)->Action_post_return_value1{ Action_post_return_value1 r = af(menu_state,ival,sval); return r; }
        [&]                         (Menu_action_1value_ret_fn_6 const &af) 							{                      auto r = af(menu_state,ival,sval); return r; },  // todo: does using "&" waste resources?
        [&]                         (Menu_action_1value_ret_fn_7 const &af) 							{                      auto r = af(menu_state,ival,ival2,sval); return r; },  // todo: does using "&" waste resources?
        //[&]                         (Menu_action_1value_ret_fn_6 const &af) 								{                      auto r = af(menu_state,ival,sval); return r; },  // todo: does using "&" waste resources?
        //[&]                         (Menu_action_1value_ret_fn_6 const &af)     ->Action_post_return_value1 {                      auto r = af(menu_state,ival,sval); return r; },  // todo: does using "&" waste resources?
        //[&]                         (Menu_action_1value_ret_fn_6 const &af)->Action_post_return_value1{                      auto r = af(menu_state,ival,sval); return r; },  // todo: does using "&" waste resources?
        //#ifndef ONE_RETURN_TYPE
        [&ival]            		(Menu_action_2values_ret_fn_1 const &af) { Action_return_2values r = af(ival); return r; },
        //[&ival]            			(Menu_action_2values_ret_fn_1 const &af) { return std::move( af(ival) ); },
        [&dval]            		(Menu_action_2values_ret_fn_2 const &af) { Action_return_2values r = af(dval); return r; },
        [&ival,&sval]      		(Menu_action_2values_ret_fn_3 const &af) { Action_return_2values r = af(ival,sval); return r; },
        [&menu_state,&ival]     (Menu_action_2values_ret_fn_4 const &af) { Action_return_2values r = af(menu_state,ival); return r; },
        [&menu_state,&dval]     (Menu_action_2values_ret_fn_5 const &af) { Action_return_2values r = af(menu_state,dval); return r; },
        //[&menu_state,&ival,&sval](Menu_action_2values_ret_fn_6 const &af){ Action_return_2values r = af(menu_state,ival,sval); return r; }
        [&menu_state,&ival,&sval](Menu_action_2values_ret_fn_6 const &af){                      	 return af(menu_state,ival,sval);}
    };
    Action_return_1value 	action_result_1value {};
    //action_result = std::visit( function_object_overload_set, 																		current_menu_option.action_fn_variant );  // todo: why must lambda funtion argument be const for only this line, not the others?
    action_result_1value = std::visit( [&](auto... args) -> Action_return_1value { return function_object_overload_set( args...); }, menu_option.action_fn_variant );
    // Now comes the part of seeing what I got back.
    switch ( action_result_1value.fns_menu_intent ) {
    case Functions_menu_intent::terminate:
        cout << "return: terminate.\n";
        break;
    case Functions_menu_intent::prior_menu:
        cout << "return: prior_menu.\n";
        break;
    case Functions_menu_intent::retain_menu:
        cout << "return: retain_menu.\n";
        break;
    default:
        assert(false);
        break;
    }
    return action_result_1value;
}

Action_return_value_variant call_menu_option_no_visit_2valsret( Menu_action const & menu_option, Menu_state & menu_state, int & ival, int & ival2, double &  dval, std::string &  sval ) {  // some of these are const because they will not change.
    auto function_object_overload_set = Overloaded { // Note: Notice that the ival and dval are captured by reference even though the signatures of the functions are capture by value.
            //       This requirement is inconsistent with the above example/ugly code. todo: TODO does this cause indefined behavior?
            // duplicates make it ambigious [&ival]            (Menu_action_1value_ret_fn &af)  { Action_return_1 r = af(ival); return r; }, // to be invoked via operator() on the function object (AKA lambda) or any callable object.
                                                   [&ival]            		(Menu_action_1value_ret_fn_1 const &af) ->Action_return_1value { Action_return_1value r = af(ival); return r; }, // to be invoked via operator() on the function object (AKA lambda) or any callable object.
                                                   [&dval]            		(Menu_action_1value_ret_fn_2 const &af) ->Action_return_1value { Action_return_1value r = af(dval); return r; },
                                                   [&ival,&sval]      		(Menu_action_1value_ret_fn_3 const &af) ->Action_return_1value { Action_return_1value r = af(ival,sval); return r; },
                                                   [&menu_state,&ival]     (Menu_action_1value_ret_fn_4 const &af) ->Action_return_1value { Action_return_1value r = af(menu_state,ival); return r; },
                                                   [&menu_state,&dval]     (Menu_action_1value_ret_fn_5 const &af) ->Action_return_1value { Action_return_1value r = af(menu_state,dval); return r; },
            //[&menu_state,&ival,&sval](Menu_action_1value_ret_fn_6 const &af)->Action_post_return_value1{ Action_post_return_value1 r = af(menu_state,ival,sval); return r; }
            [&]                         (Menu_action_1value_ret_fn_6 const &af) 							{                      auto r = af(menu_state,ival,sval); return r; },  // todo: does using "&" waste resources?
            [&]                         (Menu_action_1value_ret_fn_7 const &af) 							{                      auto r = af(menu_state,ival,ival2,sval); return r; },  // todo: does using "&" waste resources?
            //[&]                         (Menu_action_1value_ret_fn_6 const &af) 								{                      auto r = af(menu_state,ival,sval); return r; },  // todo: does using "&" waste resources?
            //[&]                         (Menu_action_1value_ret_fn_6 const &af)     ->Action_post_return_value1 {                      auto r = af(menu_state,ival,sval); return r; },  // todo: does using "&" waste resources?
            //[&]                         (Menu_action_1value_ret_fn_6 const &af)->Action_post_return_value1{                      auto r = af(menu_state,ival,sval); return r; },  // todo: does using "&" waste resources?

            [&ival]            		(Menu_action_2values_ret_fn_1 const &af) { Action_return_2values r = af(ival); return r; },
            //[&ival]            			(Menu_action_2values_ret_fn_1 const &af) { return std::move( af(ival) ); },
            [&dval]            		(Menu_action_2values_ret_fn_2 const &af) { Action_return_2values r = af(dval); return r; },
            [&ival,&sval]      		(Menu_action_2values_ret_fn_3 const &af) { Action_return_2values r = af(ival,sval); return r; },
            [&menu_state,&ival]     (Menu_action_2values_ret_fn_4 const &af) { Action_return_2values r = af(menu_state,ival); return r; },
            [&menu_state,&dval]     (Menu_action_2values_ret_fn_5 const &af) { Action_return_2values r = af(menu_state,dval); return r; },
            //[&menu_state,&ival,&sval](Menu_action_2values_ret_fn_6 const &af){ Action_return_2values r = af(menu_state,ival,sval); return r; }
            [&menu_state,&ival,&sval](Menu_action_2values_ret_fn_6 const &af){                      	 return af(menu_state,ival,sval);}
    };
    Action_return_value_variant action_result_2values {};
    // https://cpplang.slack.com/archives/C21PKDHSL/p1569203158330600
    // Required to avoid ambiguity when calling the function we must wrap the overload_set with another lambda that allows for the return value's type being of more than one type.  // todo: TODO does this additional wrapping lambda cause another level of pointer indirection?
    auto fo_return_type_overload_set = [&](auto ... args) -> Action_return_value_variant { return function_object_overload_set( args...); }; // todo: TODO is there a better way to do this?  Also I think I want to pass by reference?
    // Back to the pattern from the book.
    action_result_2values = std::visit( fo_return_type_overload_set, menu_option.action_fn_variant );

    // Now comes the part of seeing what I got back. todo: There is probably a better way to do this?
    if      (std::holds_alternative< Action_return_2values >( action_result_2values )) {
        cout << "return: int "<< std::get< Action_return_2values >( action_result_2values )<<"."<<endl;
    }
    else if (std::holds_alternative< Action_return_1value >( action_result_2values )) {
        switch (std::get< Action_return_1value>( action_result_2values ).fns_menu_intent) {
        case Functions_menu_intent::terminate:
            cout << "return: terminate.\n";
            break;
        case Functions_menu_intent::prior_menu:
            cout << "return: prior_menu.\n";
            break;
        case Functions_menu_intent::retain_menu:
            cout << "return: retain_menu.\n";
            break;
        default:
            assert(false && "missing enum.");
            break;
        }
    }
    else assert(false);
    return action_result_2values;
}

void test_1value_returned() {
    Menu_state 	menu_state 	{};  // state value
    cout << menu_state.my_int << endl;
    Menu 		menu_main 		{};
    menu_main.name = "main_menu";  // TODO??: note how the menu does not bind the menu_state and application state variables it will need when running.
    menu_main.action.emplace_back(Menu_action {"Int             ", Menu_action_1value_ret_fn_1 {action1_1}});
    menu_main.action.emplace_back(Menu_action {"Double          ", Menu_action_1value_ret_fn_2 {action1_2}});
    menu_main.action.emplace_back(Menu_action {"String          ", Menu_action_1value_ret_fn_3 {action1_3}});
    menu_main.action.emplace_back(Menu_action {"State_int       ", Menu_action_1value_ret_fn_4 {action1_4}});
    menu_main.action.emplace_back(Menu_action {"State_double    ", Menu_action_1value_ret_fn_5 {action1_5}});
    menu_main.action.emplace_back(Menu_action {"State_int_string", Menu_action_1value_ret_fn_6 {action1_6}});
    menu_main.action.emplace_back(Menu_action {"State_int2_string", Menu_action_1value_ret_fn_7 {action1_7}});
//#endif
    // The long and ugly way to call these the menu_option action_functions using if statements. Shown for comparision to a better way below.
    cout << "\n***  The long and ugly way to call these the menu_option action_functions using if statements. ***\n";
    int ival {1}, ival2 {20}; double dval {12}; std::string sval {"an_sval_"};
    for (auto & menu_option : menu_main.action) {  // test with all the various possibilities.
        ++ival; ++ival2; ++dval; menu_state.my_int++; sval += "an_sval_";
        cout << ">> ival: "<<ival<<", dval: "<<dval<< ",  menu_state.a:"<<menu_state.my_int<< endl;
        Action_return_value_variant r = call_menu_option_ifs(   menu_option, menu_state, ival, ival2, dval, sval );
    }
    // ***** NOW - A nicer way to call these the menu_option action_functions.
    cout << "\n*** A nicer way to do the above with std::visit.  ***\n";
    ival  = 10; ival2 = 300; dval  = 222.0; sval  = "an_sval_";
    for (auto & menu_option : menu_main.action) {  // test with all the various possibilities.
        ++ival; ++ival2; ++dval; menu_state.my_int++; sval += "an_sval_";
        cout << ">> ival: "<<ival<<", dval: "<<dval<< ",  menu_state.a:"<<menu_state.my_int<< endl;
        Action_return_value_variant r = call_menu_option_no_visit_1valret( menu_option, menu_state, ival, ival2, dval, sval );
    }
}

void test_2values_returned() {
    Menu_state 	menu_state 	{};  // state value
    cout << menu_state.my_int << endl;
    Menu menu_main{};
    menu_main.name = "main_menu";  // todo: note how the menu does not bind the menu_state and application state variables it will need when running.
    menu_main.action.emplace_back(Menu_action {"Int             ", Menu_action_1value_ret_fn_1 {action1_1}});
    menu_main.action.emplace_back(Menu_action {"Double          ", Menu_action_1value_ret_fn_2 {action1_2}});
    menu_main.action.emplace_back(Menu_action {"String          ", Menu_action_1value_ret_fn_3 {action1_3}});
    menu_main.action.emplace_back(Menu_action {"State_int       ", Menu_action_1value_ret_fn_4 {action1_4}});
    menu_main.action.emplace_back(Menu_action {"State_double    ", Menu_action_1value_ret_fn_5 {action1_5}});
    menu_main.action.emplace_back(Menu_action {"State_int_string", Menu_action_1value_ret_fn_6 {action1_6}});
    menu_main.action.emplace_back(Menu_action {"State_int2_string", Menu_action_1value_ret_fn_7 {action1_7}});
    menu_main.action.emplace_back(Menu_action {"Int            2", Menu_action_2values_ret_fn_1 {action2_1}});
    menu_main.action.emplace_back(Menu_action {"Double         2", Menu_action_2values_ret_fn_2 {action2_2}});
    menu_main.action.emplace_back(Menu_action {"String         2", Menu_action_2values_ret_fn_3 {action2_3}});
    menu_main.action.emplace_back(Menu_action {"State_int      2", Menu_action_2values_ret_fn_4 {action2_4}});
    menu_main.action.emplace_back(Menu_action {"State_double   2", Menu_action_2values_ret_fn_5 {action2_5}});
    menu_main.action.emplace_back(Menu_action {"State_int_strin2", Menu_action_2values_ret_fn_6 {action2_6}});
    // The long and ugly way to call these the menu_option action_functions using if statements. Shown for comparision to a better way below.
    cout << "\n***  The long and ugly way to call these the menu_option action_functions using if statements. ***\n";
    int ival {1}, ival2 {20}; double dval {12}; std::string sval {"an_sval_"};
    for (auto & menu_option : menu_main.action) {  // test with all the various possibilities.
        ++ival; ++ival2; ++dval; menu_state.my_int++; sval += "an_sval_";
        cout << ">> ival: "<<ival<<", dval: "<<dval<< ",  menu_state.a:"<<menu_state.my_int<< endl;
        Action_return_value_variant r = call_menu_option_ifs(   menu_option, menu_state, ival, ival2, dval, sval );
    }
    // ***** NOW - A nicer way to call these the menu_option action_functions.
    cout << "\n*** A nicer way to do the above with std::visit.  ***\n";
    ival  = 10; ival2 = 300; dval  = 222.0; sval  = "an_sval_";
    for (auto & menu_option : menu_main.action) {  // test with all the various possibilities.
        ++ival; ++ival2; ++dval; menu_state.my_int++; sval += "an_sval_";
        cout << ">> ival: "<<ival<<", dval: "<<dval<< ",  menu_state.a:"<<menu_state.my_int<< endl;
        Action_return_value_variant r = call_menu_option_no_visit_2valsret( menu_option, menu_state, ival, ival2, dval, sval );
    }
}

int main() {
    test_1value_returned();
    test_2values_returned();
    cout << "###" << endl;
    return 0;
}
