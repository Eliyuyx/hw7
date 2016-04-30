#include "sched.h"

#define FREEZER_TIMESLICE (100 * HZ / 1000)

/* Initialize freezer runqueue */
void init_freezer_rq(struct freezer_rq *freezer_rq) 
{
        INIT_LIST_HEAD(&freezer_rq->freezer_list);
        freezer_rq->freezer_nr_running = 0;
}


/* Add a task to the freezer runqueue and increment number of tasks */
static void
enqueue_task_freezer(struct rq *rq, struct task_struct *p, int flags)
{
        struct list_head *head = &rq->freezer.freezer_list;
        struct list_head *node = &p->freezer.run_list;
	trace_printk("MARK\n");

        // add to runqueue
        list_add_tail(node, head);

        // increment # of tasks on queue
        rq->freezer.freezer_nr_running++;
}


/* Remove task from runqueue */
static void
dequeue_task_freezer(struct rq *rq, struct task_struct *p, int flags)
{
        struct freezer_rq *freezer_rq = &rq->freezer;
        struct list_head *entry = &p->freezer.run_list;
	trace_printk("MARK\n");

        // delete from runqueue
        list_del(entry);
        
        // decrement # of tasks on queue
        freezer_rq->freezer_nr_running--;
}


/* Stub */
static void yield_task_freezer(struct rq *rq)
{
	trace_printk("MARK\n");
}

/* Stub */
static bool yield_to_task_freezer(struct rq *rq, struct task_struct *p, bool preempt)
{
	trace_printk("MARK\n");
	return false;
}


/* Stub */
static void 
check_preempt_curr_freezer(struct rq *rq, struct task_struct *p, int flags)
{
	trace_printk("MARK\n");
}


/* Choose the next task to run */
static struct task_struct * 
pick_next_task_freezer(struct rq *rq, struct task_struct *prev)
{
	struct sched_freezer_entity *next_se;
	struct freezer_rq *freezer_rq = &rq->freezer;
	trace_printk("MARK\n");

	next_se = list_first_entry_or_null(&freezer_rq->freezer_list,
			struct sched_freezer_entity, run_list);
	if (next_se)
		return container_of(next_se, struct task_struct, freezer);
	else
		return NULL;
}


/* Stub */
static void put_prev_task_freezer(struct rq *rq, struct task_struct *prev)
{
	trace_printk("MARK\n");
}


/* Stub */
static void task_fork_freezer(struct task_struct *p)
{
	trace_printk("MARK\n");
}


/* Stub */
static void task_dead_freezer(struct task_struct *p)
{
	trace_printk("MARK\n");
}


#ifdef CONFIG_SMP
/* select the CPU (runqueue) to place task on */
static int select_task_rq_freezer(struct task_struct *p, int cpu, int sd_flag, int flags)
{
	int i;
	int num;
	int new_cpu = -1;
	int min = UINT_MAX;

	struct freezer_rq *freezer_rq;
	trace_printk("MARK\n");

	for_each_possible_cpu(i) {
		freezer_rq = &cpu_rq(i)->freezer;
		num = freezer_rq->freezer_nr_running;

		if (num < min) {
			min = num;
			new_cpu = i;
		}
	}

	return new_cpu;
}
#endif


/* Stub */
static void rq_online_freezer(struct rq *rq)
{
	trace_printk("MARK\n");
}


/* Stub */
static void rq_offline_freezer(struct rq *rq)
{
	trace_printk("MARK\n");
}


/* Stub */
static void post_schedule_freezer(struct rq *rq)
{
	trace_printk("MARK\n");
}


/* Stub */
static void switched_from_freezer(struct rq *rq, struct task_struct *p)
{
	trace_printk("MARK\n");
}


/* Corresponds to a single tick of the clock */
static void task_tick_freezer(struct rq *rq, struct task_struct *p, int queued)
{
	struct sched_freezer_entity *freezer_se = &p->freezer;
	trace_printk("MARK\n");
	freezer_se->time_slice--;

	if (freezer_se->time_slice <= 0) {
		list_move_tail(&freezer_se->run_list, &rq->freezer.freezer_list);
		freezer_se->time_slice = FREEZER_TIMESLICE;
	}
}


/* Return the round robin timeslice */
static unsigned int 
get_rr_interval_freezer(struct rq *rq, struct task_struct *task)
{
	trace_printk("MARK\n");
        return FREEZER_TIMESLICE;
}


/* Stub */
static void 
prio_changed_freezer(struct rq *rq, struct task_struct *p, int oldprio)
{
	trace_printk("MARK\n");
}

/* Assign the freezer policy to the current task */
static void set_curr_task_freezer(struct rq *rq)
{
	struct task_struct *p = rq->curr;
	trace_printk("MARK\n");

	p->policy = SCHED_FREEZER;
	p->freezer.time_slice = FREEZER_TIMESLICE;
}


/* Stub */
static void switched_to_freezer(struct rq *rq, struct task_struct *p)
{
	trace_printk("MARK\n");
}


/* Stub */
static void update_curr_freezer(struct rq *rq)
{
	trace_printk("MARK\n");
}


/*
 * The Freezer Scheduler
 */
const struct sched_class freezer_sched_class = {
    .next               = &fair_sched_class,          /* nxt lowest priority */
    .enqueue_task       = enqueue_task_freezer,       
    .dequeue_task       = dequeue_task_freezer,       
    .yield_task         = yield_task_freezer,         
    .yield_to_task	= yield_to_task_freezer,
    
    .check_preempt_curr = check_preempt_curr_freezer,

    .pick_next_task     = pick_next_task_freezer,
    .put_prev_task      = put_prev_task_freezer,

#ifdef CONFIG_SMP
    .select_task_rq     = select_task_rq_freezer,
    
    .rq_online          = rq_online_freezer,
    .rq_offline         = rq_offline_freezer,
    .post_schedule      = post_schedule_freezer,
    .switched_from      = switched_from_freezer,
#endif
    
    .set_curr_task      = set_curr_task_freezer,
    .task_tick          = task_tick_freezer,
    .task_fork          = task_fork_freezer,
    .task_dead          = task_dead_freezer,
    
    .get_rr_interval    = get_rr_interval_freezer,
    
    .prio_changed       = prio_changed_freezer,
    .switched_to        = switched_to_freezer,
    
    .update_curr        = update_curr_freezer,
};
