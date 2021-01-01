using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ClassLibrary1.Entity
{
    public class Block
    {
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        [Key]
        public int Id { get; set; }

        public string Expression { get; set; }

        public override bool Equals(object? obj)
        {
            if ((obj == null) || this.GetType() != obj.GetType())
            {
                return false;
            }
            else
            {
                Block b = (Block) obj;
                return (b.Id == Id) && (b.Expression.Equals(Expression));
            }
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        public int PlaybookId { get; set; }
    }
}