#include "sched.h"
//#include <linux/sched/sysctl.h>

#define SCHED_FREEZER 7
#define FREEZER_TIMESLICE HZ

/* initialize freezer runqueue */
void init_freezer_rq(struct freezer_rq *freezer_rq) 
{
        INIT_LIST_HEAD(&freezer_rq->freezer_list);
        freezer_rq->freezer_nr_running = 0;
}


/* Add a task to the freezer runqueue and increment number of tasks */
static void
enqueue_task_freezer(struct rq *rq, struct task_struct *p, int flags)
{
        struct sched_freezer_entity *freezer_se = &p->freezer;
        struct freezer_rq *freezer_rq = freezer_se->freezer_rq;
        struct list_head *head = &freezer_rq->freezer_list;
        struct list_head *node = &freezer_se->freezer_list_node;

        // add to runqueue
        list_add_tail(node, head);

        // increment # of tasks on queue
        freezer_rq->freezer_nr_running++;
}


/* Remove task from runqueue */
static void
dequeue_task_freezer(struct rq *rq, struct task_struct *p, int flags)
{
        struct sched_freezer_entity *freezer_se = &p->freezer;
        struct freezer_rq *freezer_rq = freezer_se->freezer_rq;
        struct list_head *entry = &freezer_se->freezer_list_node;

        // delete from runqueue
        list_del(entry);
        
        // decrement # of tasks on queue
        freezer_rq->freezer_nr_running--;
}


/* Basically dequeues then enqueues a task (moves to end) */
static void yield_task_freezer(struct rq *rq)
{
        struct sched_freezer_entity *freezer_se = &rq->curr->freezer;
        struct freezer_rq *freezer_rq = freezer_se->freezer_rq;
        struct list_head *head = &freezer_rq->freezer_list;
        struct list_head *entry = &freezer_se->freezer_list_node;

        // move task to end of queue
        list_move_tail(entry, head);
}


/* No preemption in freezer, so not needed. */
static void 
check_preempt_curr_freezer(struct rq *rq, struct task_struct *p, int flags)
{
}


/*  */
static struct task_struct * 
pick_next_task_freezer(struct rq *rq, struct task_struct *prev)
{
        struct sched_freezer_entity *next_se;
        struct freezer_rq *freezer_rq = &rq->freezer;
        struct task_struct *next;
        put_prev_task(rq, prev);

        next_se = list_entry(freezer_rq->freezer_list.next, 
                        struct sched_freezer_entity, freezer_list_node);

        next = container_of(next_se, struct task_struct, freezer);

        return next;
}


/*  */
static void put_prev_task_freezer(struct rq *rq, struct task_struct *prev)
{
        struct sched_entity *prev_se = &prev->se;
        
        // if still on runqueue then put back on freezer queue
        if (prev_se->on_rq)
                enqueue_task_freezer(rq, prev, 0);

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
        struct sched_freezer_entity *freezer_se = &p->freezer;
        struct freezer_rq *freezer_rq = freezer_se->freezer_rq;
        struct list_head *head = &freezer_rq->freezer_list;
        struct list_head *entry = &freezer_se->freezer_list_node;

        // move task to end of queue if not only task on queue
        if (entry->prev != entry->next)
                list_move_tail(entry, head);
}


/*  */
static unsigned int 
get_rr_interval_freezer(struct rq *rq, struct task_struct *task)
{
        return FREEZER_TIMESLICE;
}


/* No priority. Not needed. */
static void 
prio_changed_freezer(struct rq *rq, struct task_struct *p, int oldprio)
{
}


/*  */
static void switched_to_freezer(struct rq *rq, struct task_struct *p)
{
    // TODO:
}


/* No stat tracking so not needed. */
static void update_curr_freezer(struct rq *rq)
{
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
//    .task_fork          = task_fork_freezer,
//    .task_dead          = task_dead_freezer,
    
    .get_rr_interval    = get_rr_interval_freezer,
    
    .prio_changed       = prio_changed_freezer,
    .switched_to        = switched_to_freezer,
    
    .update_curr        = update_curr_freezer,
};
