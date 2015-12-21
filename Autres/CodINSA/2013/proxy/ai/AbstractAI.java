/*  1:   */ package ai;
/*  2:   */ 
/*  3:   */ import proxy.Proxy;
/*  4:   */ 
/*  5:   */ public abstract class AbstractAI
/*  6:   */ {
/*  7:   */   protected Proxy game;
/*  8:   */   
/*  9:   */   public AbstractAI(String ip, int port)
/* 10:   */   {
/* 11:11 */     this.game = new Proxy(ip, port, this);
/* 12:   */   }
/* 13:   */   
/* 14:   */   public abstract void think();
/* 15:   */   
/* 16:   */   public void end() {}
/* 17:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     ai.AbstractAI
 * JD-Core Version:    0.7.0.1
 */