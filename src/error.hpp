#ifndef BOX2D_ERROR_MACROS
#define BOX2D_ERROR_MACROS


#ifdef DEBUG_ENABLED
#define ERR_FAIL_COND_DEBUG(m_cond)                                                                             \
	if (unlikely(m_cond)) {                                                                                     \
		::godot::_err_print_error(FUNCTION_STR, __FILE__, __LINE__, "Condition \"" _STR(m_cond) "\" is true."); \
		return;                                                                                                 \
	} else                                                                                                      \
		((void)0)
#else
#define ERR_FAIL_COND_DEBUG(m_cond)                                                                             \
	if (unlikely(m_cond)) {                                                                                     \
		return;                                                                                                 \
	} else                                                                                                      \
		((void)0)
#endif

#ifdef DEBUG_ENABLED
#define ERR_FAIL_V_DEBUG(m_retval)                                                                                         \
	if (true) {                                                                                                            \
		::godot::_err_print_error(FUNCTION_STR, __FILE__, __LINE__, "Method/function failed. Returning: " _STR(m_retval)); \
		return m_retval;                                                                                                   \
	} else                                                                                                                 \
		((void)0)
#else
#define ERR_FAIL_V_DEBUG(m_retval)                                                                                         \
	if (true) {																											   \
		return m_retval;                                                                                                   \
	} else                                                                                                                 \
		((void)0)
#endif


#ifdef DEBUG_ENABLED
#define ERR_PRINT_DEBUG(m_msg)
	::godot::_err_print_error(FUNCTION_STR, __FILE__, __LINE__, m_msg)
#else
#define ERR_PRINT_DEBUG(m_retval)
#endif

#endif /* BOX2D_ERROR_MACROS */
