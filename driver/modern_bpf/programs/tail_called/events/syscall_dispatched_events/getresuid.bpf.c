/*
 * Copyright (C) 2022 The Falco Authors.
 *
 * This file is dual licensed under either the MIT or GPL 2. See MIT.txt
 * or GPL2.txt for full copies of the license.
 */

#include <helpers/interfaces/fixed_size_event.h>
#include <helpers/interfaces/variable_size_event.h>

/*=============================== ENTER EVENT ===========================*/

SEC("tp_btf/sys_enter")
int BPF_PROG(getresuid_e,
	     struct pt_regs *regs,
	     long id)
{
	struct auxiliary_map *auxmap = auxmap__get();
	if(!auxmap)
	{
		return 0;
	}

	auxmap__preload_event_header(auxmap, PPME_SYSCALL_GETRESUID_E);

	/*=============================== COLLECT PARAMETERS  ===========================*/

	/*=============================== COLLECT PARAMETERS  ===========================*/

	auxmap__submit_event(auxmap);

	return 0;
}

/*=============================== ENTER EVENT ===========================*/

/*=============================== EXIT EVENT ===========================*/

SEC("tp_btf/sys_exit")
int BPF_PROG(getresuid_x,
	     struct pt_regs *regs,
	     long ret)
{
	struct auxiliary_map *auxmap = auxmap__get();
	if(!auxmap)
	{
		return 0;
	}

	auxmap__preload_event_header(auxmap, PPME_SYSCALL_GETRESUID_X);

	/*=============================== COLLECT PARAMETERS  ===========================*/

        /* Parameter 1: res (type: PT_ERRNO) */
        auxmap__store_s64_param(auxmap, (s64)ret);

	/* Parameter 2: ruid (type: PT_UINT32) */
	uid_t uid;
	unsigned long uid_pointer = extract__syscall_argument(regs, 0);
	bpf_probe_read_user((void *)&uid, sizeof(uid_t), (void *)uid_pointer); 
	auxmap__store_u32_param(auxmap, (u32)uid);

	/* Parameter 3: euid (type: PT_UINT32) */
	uid_pointer = extract__syscall_argument(regs, 1);
	bpf_probe_read_user((void *)&uid, sizeof(uid_t), (void *)uid_pointer);
	auxmap__store_u32_param(auxmap, (u32)uid);

	/* Parameter 4: suid (type: PT_UINT32) */
	uid_pointer = extract__syscall_argument(regs, 2);
	bpf_probe_read_user((void *)&uid, sizeof(uid_t), (void *)uid_pointer);
	auxmap__store_u32_param(auxmap, (u32)uid);

	/*=============================== COLLECT PARAMETERS  ===========================*/

	auxmap__submit_event(auxmap);

	return 0;
}

/*=============================== EXIT EVENT ===========================*/
