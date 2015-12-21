/*   1:    */ package common;
/*   2:    */ 
/*   3:    */ import java.util.AbstractCollection;
/*   4:    */ import java.util.Collection;
/*   5:    */ import java.util.Iterator;
/*   6:    */ 
/*   7:    */ public abstract interface CollectionView<T>
/*   8:    */   extends Viewable.View, Iterable<T>
/*   9:    */ {
/*  10:    */   public abstract Collection<T> asUnmodifiableCollection();
/*  11:    */   
/*  12:    */   @Deprecated
/*  13:    */   public abstract boolean contains(Object paramObject);
/*  14:    */   
/*  15:    */   @Deprecated
/*  16:    */   public abstract boolean containsAll(Collection<?> paramCollection);
/*  17:    */   
/*  18:    */   public abstract boolean containsTypeSafe(T paramT);
/*  19:    */   
/*  20:    */   public abstract <U extends T> boolean containsTypeSafe(Collection<U> paramCollection);
/*  21:    */   
/*  22:    */   public abstract boolean isEmpty();
/*  23:    */   
/*  24:    */   public abstract Iterator<T> iterator();
/*  25:    */   
/*  26:    */   public abstract int size();
/*  27:    */   
/*  28:    */   public abstract Object[] toArray();
/*  29:    */   
/*  30:    */   public abstract <U> U[] toArray(U[] paramArrayOfU);
/*  31:    */   
/*  32:    */   public static class ShallowOf<T>
/*  33:    */     extends AbstractCollection<T>
/*  34:    */     implements CollectionView<T>
/*  35:    */   {
/*  36:    */     final Collection<T> delegate;
/*  37:    */     
/*  38:    */     public ShallowOf(Collection<T> src)
/*  39:    */     {
/*  40: 45 */       this.delegate = src;
/*  41:    */     }
/*  42:    */     
/*  43:    */     protected Collection<T> delegate()
/*  44:    */     {
/*  45: 49 */       return this.delegate;
/*  46:    */     }
/*  47:    */     
/*  48:    */     public int size()
/*  49:    */     {
/*  50: 52 */       return this.delegate.size();
/*  51:    */     }
/*  52:    */     
/*  53:    */     public Collection<T> asUnmodifiableCollection()
/*  54:    */     {
/*  55: 57 */       return this;
/*  56:    */     }
/*  57:    */     
/*  58:    */     public Iterator<T> iterator()
/*  59:    */     {
/*  60: 73 */       return this.delegate.iterator();
/*  61:    */     }
/*  62:    */     
/*  63:    */     public boolean containsTypeSafe(T arg)
/*  64:    */     {
/*  65: 91 */       return contains(arg);
/*  66:    */     }
/*  67:    */     
/*  68:    */     public <U extends T> boolean containsTypeSafe(Collection<U> arg)
/*  69:    */     {
/*  70: 96 */       return containsAll(arg);
/*  71:    */     }
/*  72:    */   }
/*  73:    */   
/*  74:    */   public static class Transform<U>
/*  75:    */     extends AbstractCollection<U>
/*  76:    */     implements CollectionView<U>, CollectionWrapper
/*  77:    */   {
/*  78:    */     final Collection<Object> delegate;
/*  79:    */     final Util.Converter<Object, U> transformer;
/*  80:    */     
/*  81:    */     public <T> Transform(Collection<T> src, Util.Converter<T, U> transformer)
/*  82:    */     {
/*  83:128 */       this.delegate = src;
/*  84:129 */       this.transformer = transformer;
/*  85:    */     }
/*  86:    */     
/*  87:    */     public Collection<?> delegate()
/*  88:    */     {
/*  89:134 */       return this.delegate;
/*  90:    */     }
/*  91:    */     
/*  92:    */     public int size()
/*  93:    */     {
/*  94:137 */       return this.delegate.size();
/*  95:    */     }
/*  96:    */     
/*  97:    */     public Collection<U> asUnmodifiableCollection()
/*  98:    */     {
/*  99:141 */       return this;
/* 100:    */     }
/* 101:    */     
/* 102:    */     public Iterator<U> iterator()
/* 103:    */     {
/* 104:145 */       final Iterator<Object> ite = this.delegate.iterator();
/* 105:146 */       new Iterator()
/* 106:    */       {
/* 107:    */         public boolean hasNext()
/* 108:    */         {
/* 109:148 */           return ite.hasNext();
/* 110:    */         }
/* 111:    */         
/* 112:    */         public U next()
/* 113:    */         {
/* 114:152 */           return CollectionView.Transform.this.transformer.convert(ite.next());
/* 115:    */         }
/* 116:    */         
/* 117:    */         public void remove()
/* 118:    */         {
/* 119:155 */           throw new UnsupportedOperationException();
/* 120:    */         }
/* 121:    */       };
/* 122:    */     }
/* 123:    */     
/* 124:    */     public boolean containsTypeSafe(U arg)
/* 125:    */     {
/* 126:162 */       return contains(arg);
/* 127:    */     }
/* 128:    */     
/* 129:    */     public <W extends U> boolean containsTypeSafe(Collection<W> arg)
/* 130:    */     {
/* 131:167 */       return containsAll(arg);
/* 132:    */     }
/* 133:    */   }
/* 134:    */   
/* 135:    */   public static class Of<V extends Viewable.View>
/* 136:    */     extends AbstractCollection<V>
/* 137:    */     implements CollectionView<V>
/* 138:    */   {
/* 139:    */     final Collection<Viewable<V>> delegate;
/* 140:    */     
/* 141:    */     public <T extends Viewable<V>> Of(Collection<T> src)
/* 142:    */     {
/* 143:190 */       this.delegate = src;
/* 144:    */     }
/* 145:    */     
/* 146:    */     public int size()
/* 147:    */     {
/* 148:197 */       return this.delegate.size();
/* 149:    */     }
/* 150:    */     
/* 151:    */     public Collection<V> asUnmodifiableCollection()
/* 152:    */     {
/* 153:201 */       return this;
/* 154:    */     }
/* 155:    */     
/* 156:    */     public Iterator<V> iterator()
/* 157:    */     {
/* 158:226 */       final Iterator<Viewable<V>> ite = this.delegate.iterator();
/* 159:227 */       new Iterator()
/* 160:    */       {
/* 161:    */         public boolean hasNext()
/* 162:    */         {
/* 163:229 */           return ite.hasNext();
/* 164:    */         }
/* 165:    */         
/* 166:    */         public V next()
/* 167:    */         {
/* 168:232 */           return ((Viewable)ite.next()).view();
/* 169:    */         }
/* 170:    */         
/* 171:    */         public void remove()
/* 172:    */         {
/* 173:235 */           throw new UnsupportedOperationException();
/* 174:    */         }
/* 175:    */       };
/* 176:    */     }
/* 177:    */     
/* 178:    */     public boolean containsTypeSafe(V arg)
/* 179:    */     {
/* 180:266 */       return contains(arg);
/* 181:    */     }
/* 182:    */     
/* 183:    */     public <U extends V> boolean containsTypeSafe(Collection<U> arg)
/* 184:    */     {
/* 185:271 */       return containsAll(arg);
/* 186:    */     }
/* 187:    */   }
/* 188:    */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.CollectionView
 * JD-Core Version:    0.7.0.1
 */