/*  1:   */ package ai;
/*  2:   */ 
/*  3:   */ import command.MoveCommand;
/*  4:   */ import common.CollectionView;
/*  5:   */ import common.MapView;
/*  6:   */ import java.io.PrintStream;
/*  7:   */ import java.util.Iterator;
/*  8:   */ import java.util.Random;
/*  9:   */ import model.Base.BasicView;
/* 10:   */ import model.Plane.FullView;
/* 11:   */ import proxy.Proxy;
/* 12:   */ 
/* 13:   */ public class MoveAI
/* 14:   */   extends AbstractAI
/* 15:   */ {
/* 16:   */   public MoveAI(String ip, int port)
/* 17:   */   {
/* 18:16 */     super(ip, port);
/* 19:   */   }
/* 20:   */   
/* 21:   */   public void think()
/* 22:   */   {
/* 23:21 */     Random r = new Random();
/* 24:   */     Iterator localIterator;
/* 25:27 */     for (;; localIterator.hasNext())
/* 26:   */     {
/* 27:24 */       this.game.updateSimFrame();
/* 28:25 */       MapView<Integer, Base.BasicView> bases = this.game.getAllBases();
/* 29:   */       
/* 30:27 */       localIterator = this.game.getMyPlanes().valuesView().iterator(); continue;Plane.FullView p = (Plane.FullView)localIterator.next();
/* 31:30 */       if (bases.size() > 0)
/* 32:   */       {
/* 33:31 */         int i = r.nextInt(bases.size());
/* 34:   */         
/* 35:   */ 
/* 36:   */ 
/* 37:   */ 
/* 38:36 */         Base.BasicView b = (Base.BasicView)bases.get(Integer.valueOf(i));
/* 39:   */         
/* 40:   */ 
/* 41:   */ 
/* 42:   */ 
/* 43:   */ 
/* 44:   */ 
/* 45:   */ 
/* 46:   */ 
/* 47:   */ 
/* 48:   */ 
/* 49:47 */         this.game.sendCommand(new MoveCommand(p, b.position()));
/* 50:   */       }
/* 51:   */     }
/* 52:   */   }
/* 53:   */   
/* 54:   */   public static void main(String[] args)
/* 55:   */   {
/* 56:56 */     if (args.length != 2)
/* 57:   */     {
/* 58:58 */       System.out.println("Usage : java MoveAI ip port");
/* 59:59 */       System.exit(1);
/* 60:   */     }
/* 61:61 */     String ip = args[0];
/* 62:62 */     int port = Integer.parseInt(args[1]);
/* 63:   */     
/* 64:64 */     AbstractAI ai = new MoveAI(ip, port);
/* 65:65 */     ai.think();
/* 66:   */   }
/* 67:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     ai.MoveAI
 * JD-Core Version:    0.7.0.1
 */