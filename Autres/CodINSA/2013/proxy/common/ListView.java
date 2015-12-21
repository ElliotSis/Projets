/*   1:    */ package common;
/*   2:    */ 
/*   3:    */ import java.util.AbstractList;
/*   4:    */ import java.util.Collection;
/*   5:    */ import java.util.List;
/*   6:    */ import java.util.ListIterator;
/*   7:    */ 
/*   8:    */ public abstract interface ListView<T>
/*   9:    */   extends CollectionView<T>
/*  10:    */ {
/*  11:    */   public abstract List<T> asUnmodifiableList();
/*  12:    */   
/*  13:    */   public abstract T get(int paramInt);
/*  14:    */   
/*  15:    */   public abstract int indexOf(Object paramObject);
/*  16:    */   
/*  17:    */   public abstract int lastIndexOf(Object paramObject);
/*  18:    */   
/*  19:    */   public abstract ListIterator<T> listIterator();
/*  20:    */   
/*  21:    */   public abstract ListIterator<T> listIterator(int paramInt);
/*  22:    */   
/*  23:    */   public abstract List<T> subList(int paramInt1, int paramInt2);
/*  24:    */   
/*  25:    */   public static class ShallowOf<T>
/*  26:    */     extends AbstractList<T>
/*  27:    */     implements ListView<T>
/*  28:    */   {
/*  29:    */     final List<T> delegate;
/*  30:    */     
/*  31:    */     public ShallowOf(List<T> src)
/*  32:    */     {
/*  33: 38 */       this.delegate = src;
/*  34:    */     }
/*  35:    */     
/*  36:    */     public List<T> asUnmodifiableList()
/*  37:    */     {
/*  38: 56 */       return this;
/*  39:    */     }
/*  40:    */     
/*  41:    */     public Collection<T> asUnmodifiableCollection()
/*  42:    */     {
/*  43: 62 */       return this;
/*  44:    */     }
/*  45:    */     
/*  46:    */     public T get(int arg0)
/*  47:    */     {
/*  48: 66 */       return this.delegate.get(arg0);
/*  49:    */     }
/*  50:    */     
/*  51:    */     public int size()
/*  52:    */     {
/*  53: 68 */       return this.delegate.size();
/*  54:    */     }
/*  55:    */     
/*  56:    */     public boolean containsTypeSafe(T arg)
/*  57:    */     {
/*  58: 92 */       return contains(arg);
/*  59:    */     }
/*  60:    */     
/*  61:    */     public <U extends T> boolean containsTypeSafe(Collection<U> arg)
/*  62:    */     {
/*  63: 97 */       return containsAll(arg);
/*  64:    */     }
/*  65:    */   }
/*  66:    */   
/*  67:    */   public static class Transform<U>
/*  68:    */     extends AbstractList<U>
/*  69:    */     implements ListView<U>, CollectionWrapper
/*  70:    */   {
/*  71:    */     final List<?> delegate;
/*  72:    */     final Util.Converter<Object, U> transformer;
/*  73:    */     
/*  74:    */     public <T> Transform(List<T> src, Util.Converter<T, U> transformer)
/*  75:    */     {
/*  76:116 */       this.delegate = src;
/*  77:117 */       this.transformer = transformer;
/*  78:    */     }
/*  79:    */     
/*  80:    */     public U get(int arg0)
/*  81:    */     {
/*  82:120 */       return this.transformer.convert(this.delegate.get(arg0));
/*  83:    */     }
/*  84:    */     
/*  85:    */     public int size()
/*  86:    */     {
/*  87:122 */       return this.delegate.size();
/*  88:    */     }
/*  89:    */     
/*  90:    */     public Collection<U> asUnmodifiableCollection()
/*  91:    */     {
/*  92:124 */       return this;
/*  93:    */     }
/*  94:    */     
/*  95:    */     public List<U> asUnmodifiableList()
/*  96:    */     {
/*  97:126 */       return this;
/*  98:    */     }
/*  99:    */     
/* 100:    */     public List<?> delegate()
/* 101:    */     {
/* 102:129 */       return this.delegate;
/* 103:    */     }
/* 104:    */     
/* 105:    */     public boolean containsTypeSafe(U arg)
/* 106:    */     {
/* 107:140 */       return contains(arg);
/* 108:    */     }
/* 109:    */     
/* 110:    */     public <W extends U> boolean containsTypeSafe(Collection<W> arg)
/* 111:    */     {
/* 112:145 */       return containsAll(arg);
/* 113:    */     }
/* 114:    */   }
/* 115:    */   
/* 116:    */   public static class Of<V extends Viewable.View>
/* 117:    */     extends AbstractList<V>
/* 118:    */     implements ListView<V>
/* 119:    */   {
/* 120:    */     final List<Viewable<V>> delegate;
/* 121:    */     
/* 122:    */     public <T extends Viewable<V>> Of(List<T> src)
/* 123:    */     {
/* 124:167 */       this.delegate = src;
/* 125:    */     }
/* 126:    */     
/* 127:    */     public V get(int arg0)
/* 128:    */     {
/* 129:170 */       return ((Viewable)this.delegate.get(arg0)).view();
/* 130:    */     }
/* 131:    */     
/* 132:    */     public int size()
/* 133:    */     {
/* 134:172 */       return this.delegate.size();
/* 135:    */     }
/* 136:    */     
/* 137:    */     public Collection<V> asUnmodifiableCollection()
/* 138:    */     {
/* 139:174 */       return this;
/* 140:    */     }
/* 141:    */     
/* 142:    */     public List<V> asUnmodifiableList()
/* 143:    */     {
/* 144:176 */       return this;
/* 145:    */     }
/* 146:    */     
/* 147:    */     public boolean containsTypeSafe(V arg)
/* 148:    */     {
/* 149:180 */       return contains(arg);
/* 150:    */     }
/* 151:    */     
/* 152:    */     public <U extends V> boolean containsTypeSafe(Collection<U> arg)
/* 153:    */     {
/* 154:185 */       return containsAll(arg);
/* 155:    */     }
/* 156:    */   }
/* 157:    */ }


/* Location:           D:\CODinsa\Partage\public-2014\proxy.jar
 * Qualified Name:     common.ListView
 * JD-Core Version:    0.7.0.1
 */