#include "sched.h"
//#include <linux/sched/sysctl.h>

/*  */
static void
enqueue_task_freezer(struct rq *rq, struct task_struct *p, int flags)
{
    // TODO: 
}


/*  */
static void
dequeue_task_freezer(struct rq *rq, struct task_struct *p, int flags)
{
    // TODO:
}


/*  */
static void yield_task_freezer(struct rq *rq)
{
    // TODO:
}


/*  */
static void 
check_preempt_curr_freezer(struct rq *rq, struct task_struct *p, int flags)
{
    // TODO:
}


/*  */
static struct task_struct * 
pick_next_task_freezer(struct rq *rq, struct task_struct *p)
{
    // TODO:
    return NULL;
}


/*  */
static void put_prev_task_freezer(struct rq *rq, struct task_struct *p)
{
    // TODO: 
}


#ifdef CONFIG_SMP
/*  */
static int select_task_rq_freezer(struct task_struct *p, int cpu, int sd_flag, int flags)
{
    // TODO:
    return 0;
}
#endif


/*  */
static void 
set_cpus_allowed_freezer(struct task_struct *p, const struct cpumask *new_mask)
{
    // TODO:
}


/*  */
static void rq_online_freezer(struct rq *rq)
{
    // TODO:
}


/*  */
static void rq_offline_freezer(struct rq *rq)
{
    // TODO:
}


/*  */
static void post_schedule_freezer(struct rq *rq)
{
    // TODO:
}


/*  */
static void task_woken_freezer(struct rq *rq, struct task_struct *p)
{
    // TODO:
}


/*  */
static void switched_from_freezer(struct rq *rq, struct task_struct *p)
{
    // TODO:
}


/*  */
static void set_curr_task_freezer(struct rq *rq)
{
    // TODO:
}


/*  */
static void task_tick_freezer(struct rq *rq, struct task_struct *p, int queued)
{
    // TODO:
}


/*  */
static unsigned int 
get_rr_interval_freezer(struct rq *rq, struct task_struct *task)
{
    // TODO:
    return 0;
}


/*  */
static void 
prio_changed_freezer(struct rq *rq, struct task_struct *p, int oldprio)
{
    // TODO:
}


/*  */
static void switched_to_freezer(struct rq *rq, struct task_struct *p)
{
    // TODO:
}


/*  */
static void update_curr_freezer(struct rq *rq)
{
    // TODO
}


/*
 * The Freezer Scheduler
 */
const struct sched_class freezer_sched_class = {
    .next               = &fair_sched_class,          /* nxt lowest priority */
    .enqueue_task       = enqueue_task_freezer,       
    .dequeue_task       = dequeue_task_freezer,       
    .yield_task         = yield_task_freezer,         
    
    .check_preempt_curr = check_preempt_curr_freezer,

    .pick_next_task     = pick_next_task_freezer,
    .put_prev_task      = put_prev_task_freezer,

#ifdef CONFIG_SMP
    .select_task_rq     = select_task_rq_freezer,
    
    .set_cpus_allowed   = set_cpus_allowed_freezer,
    .rq_online          = rq_online_freezer,
    .rq_offline         = rq_offline_freezer,
    .post_schedule      = post_schedule_freezer,
    .task_woken         = task_woken_freezer,
    .switched_from      = switched_from_freezer,
#endif
    
    .set_curr_task      = set_curr_task_freezer,
    .task_tick          = task_tick_freezer,
    
    .get_rr_interval    = get_rr_interval_freezer,
    
    .prio_changed       = prio_changed_freezer,
    .switched_to        = switched_to_freezer,
    
    .update_curr        = update_curr_freezer,
};
