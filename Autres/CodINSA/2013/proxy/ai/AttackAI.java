/*  1:   */ package ai;
/*  2:   */ 
/*  3:   */ import command.AttackCommand;
/*  4:   */ import common.CollectionView;
/*  5:   */ import common.MapView;
/*  6:   */ import java.io.PrintStream;
/*  7:   */ import java.util.Iterator;
/*  8:   */ import java.util.Random;
/*  9:   */ import model.Base.BasicView;
/* 10:   */ import model.Plane.BasicView;
/* 11:   */ import model.Plane.FullView;
/* 12:   */ import proxy.Proxy;
/* 13:   */ 
/* 14:   */ public class AttackAI
/* 15:   */   extends AbstractAI
/* 16:   */ {
/* 17:   */   public AttackAI(String ip, int port)
/* 18:   */   {
/* 19:20 */     super(ip, port);
/* 20:   */   }
/* 21:   */   
/* 22:   */   public void think()
/* 23:   */   {
/* 24:25 */     Random r = new Random();
/* 25:   */     Iterator localIterator;
/* 26:34 */     for (;; localIterator.hasNext())
/* 27:   */     {
/* 28:28 */       this.game.updateSimFrame();
/* 29:   */       
/* 30:   */ 
/* 31:31 */       MapView<Integer, Base.BasicView> bases = this.game.getAllBases();
/* 32:32 */       MapView<Integer, Plane.BasicView> ennemy_planes = this.game.getEnnemyPlanes();
/* 33:   */       
/* 34:34 */       localIterator = this.game.getMyPlanes().valuesView().iterator(); continue;Plane.FullView p = (Plane.FullView)localIterator.next();
/* 35:37 */       if (bases.size() > 0)
/* 36:   */       {
/* 37:38 */         int i = r.nextInt(bases.size());
/* 38:   */         
/* 39:   */ 
/* 40:   */ 
/* 41:   */ 
/* 42:43 */         Base.BasicView b = (Base.BasicView)bases.get(Integer.valueOf(i));
/* 43:57 */         if (ennemy_planes.size() != 0) {
/* 44:58 */           this.game.sendCommand(new AttackCommand(p, (Plane.BasicView)ennemy_planes.valuesView().iterator().next()));
/* 45:   */         }
/* 46:   */       }
/* 47:   */     }
/* 48:   */   }
/* 49:   */   
/* 50:   */   public static void main(String[] args)
/* 51:   */   {
/* 52:69 */     if (args.length != 2)
/* 53:   */     {
/* 54:71 */       System.out.println("Usage : java AttackAI ip port");
/* 55:72 */       System.exit(1);
/* 56:   */     }
/* 57:74 */     String ip = args[0];
/* 58:75 */     int port = Integer.parseInt(args[1]);
/* 59:   */     
/* 60:77 */     AbstractAI ai = new AttackAI(ip, port);
/* 61:78 */     ai.think();
/* 62:   */   }
/* 63:   */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     ai.AttackAI
 * JD-Core Version:    0.7.0.1
 */