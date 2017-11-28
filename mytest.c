//
// Created by shenglong on 2017/11/8.
//

#include <signal.h>
//event.c文件
// this is bullshit
int
evmap_signal_add(struct event_base *base, int sig, struct event *ev)
{
  const struct eventop *evsel = base->evsigsel;
  struct event_signal_map *map = &base->sigmap;
  struct evmap_signal *ctx = NULL;

  if (sig >= map->nentries) {

    if (evmap_make_space(map, sig, sizeof(struct evmap_signal *)) == -1)
      return (-1);
  }

  //无论是GET_SIGNAL_SLOT_AND_CTOR还是GET_IO_SLOT_AND_CTOR，其作用
  //都是在数组(哈希表也是一个数组)中找到fd中的一个结构。
  //GET_SIGNAL_SLOT_AND_CTOR(ctx, map, sig, evmap_signal, evmap_signal_init,
  //base->evsigsel->fdinfo_len);
  do
  {
    //同event_io_map一样，同一个信号或者fd可以被多次event_new、event_add
    //所以，当同一个信号或者fd被多次event_add后，entries[sig]就不会为NULL
    if ((map)->entries[sig] == NULL)//第一次
    {
      //evmap_signal成员只有一个TAILQ_HEAD (event_list, event);
      //可以说evmap_signal本身就是一个TAILQ_HEAD
      //这个赋值操作很重要。
      (map)->entries[sig] = mm_calloc(1, sizeof(struct evmap_signal)
                                         + base->evsigsel->fdinfo_len
      );

      if (EVUTIL_UNLIKELY((map)->entries[sig] == NULL))
        return (-1);


      //内部调用TAILQ_INIT(&entry->events);
      (evmap_signal_init)((struct evmap_signal *)(map)->entries[sig]);
    }

    (ctx) = (struct evmap_signal *)((map)->entries[sig]);
  } while (0);

  ...

  //将所有有相同信号值的event连起来
  TAILQ_INSERT_TAIL(&ctx->events, ev, ev_signal_next);

  return (1);
}
