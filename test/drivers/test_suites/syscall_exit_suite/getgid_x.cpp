#include "../../event_class/event_class.h"

#ifdef __NR_getgid
TEST(SyscallExit, getgidX)
{
	auto evt_test = get_syscall_event_test(__NR_getgid, EXIT_EVENT);

	evt_test->enable_capture();

	/*=============================== TRIGGER SYSCALL ===========================*/

	assert_syscall_state(SYSCALL_SUCCESS, "getgid", syscall(__NR_getgid), NOT_EQUAL, -1);
	uid_t uid = syscall(__NR_getgid);

	/*=============================== TRIGGER SYSCALL ===========================*/

	evt_test->disable_capture();

	evt_test->assert_event_presence();

	if(HasFatalFailure())
	{
		return;
	}

	evt_test->parse_event();

	evt_test->assert_header();

	/*=============================== ASSERT PARAMETERS  ===========================*/

	/* Parameter 1: res (type: PT_UID) */
	evt_test->assert_numeric_param(1, (uint32_t)uid);

	/*=============================== ASSERT PARAMETERS  ===========================*/

	evt_test->assert_num_params_pushed(1);
}
#endif
