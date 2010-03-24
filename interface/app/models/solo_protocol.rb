class Solo_Protocol < ActiveRecord::Base
  validates_numericality_of :protocol, :only_integer => true, :message => "Protocol number must be an integer"
  validates_inclusion_of :protocol, :in => 0..140, :message => "Valid protocol numbers are between 0 and 141 only."
end
