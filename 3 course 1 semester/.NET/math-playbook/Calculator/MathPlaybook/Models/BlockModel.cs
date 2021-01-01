using System.Collections.Generic;
using ClassLibrary1.Entity;

namespace MathPlaybook
{
    public class BlockModel
    {
        public BlockModel(List<Block> blocks, Dictionary<int, double> calculatedValues)
        {
            Blocks = blocks;
            CalculatedValues = calculatedValues;
        }

        public BlockModel(List<Block> blocks)
        {
            Blocks = blocks;
            CalculatedValues = new Dictionary<int, double>();
        }

        public List<Block> Blocks { get; set; }
        public Dictionary<int, double> CalculatedValues { get; set; }
    }
}