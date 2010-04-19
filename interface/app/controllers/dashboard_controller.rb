class DashboardController < ApplicationController
 
  # GET /dashboard
  def index
    @protocols = Protocol.find(:all, :conditions => ['name LIKE ?', "%#{params[:search]}%"])
    @page_title = "Firewall Performance Overview"
    session[:avg] ||= 11
    session[:peak] ||= 15
    @peak = session[:peak]
    @avg = session[:avg]
    @nav_over = "current"
    @chart = open_flash_chart_object(975,300,"/dashboard/init_chart")

    respond_to do |format|
      format.html { render :overview }
    end
  end
 
  def edit_num
    if params[:editorId] == "avg"
      session[:avg] = params[:value]
    end

    if params[:editorId] == "peak"
      session[:peak] == params[:value]
    end
    render :update do |page|
      page.reload
    end
  end
 
  # GET /dashboard/ip
  def ip
    @page_title = "IP Configuration"
    @blockeds = Blocked.find(:all, 
                             :select => 'ip, name, port',
                             :conditions => ['user_id = ?', current_user.id],
                             :joins => :protocols) do #.map do |cur|
   # blockeds = Blocked.all.map do |cur|
     # @blockedsnew = @blockeds.map do |cur|
     # cur.name = $protocol_ids[cur.name.to_i] if cur.name
    #  cur
    #  end

    if params[:_search] == "true"
      ip =~ "%#{params[:ip]}%" if params[:ip].present?
      protocol =~ "%#{params[:protocol]}%" if params[:protocol].present?
      port =~ "%#{params[:port]}%" if params[:port].present?
    end
    paginate :page => params[:page], :per_page => params[:rows]
    order_by "#{params[:sidx]} #{params[:sord]}"
    end
    respond_to do |format|
      @nav_ip = "current"
      format.html
      format.json { render :json => @blockeds.to_jqgrid_json([:ip, :name, :port],
                                     params[:page],params[:rows], @blockeds.total_entries) }

      format.js

    end
  end
 
  # DELETE /dashboard/ip/1
  def destroy
    if params[:ip_list]
      Blocked.find(params[:ip_list]).destroy   
    elsif params[:proto_list]
      Protocol.find(params[:proto_list]).destroy
    elsif params[:port_list]
      Blocked.find(params[:port_list]).destroy
    end
 
    respond_to do |format|
      format.html { redirect_to :action => 'ip'  }
      format.xml  { head :ok }
    end
  end
 
  # POST /dashboard
  def create
    @ip = Array.new
    (params[:blocked][:ip_1]..params[:blocked][:ip2_1]).each do |a|
       (params[:blocked][:ip_2]..params[:blocked][:ip2_2]).each do |b|
          (params[:blocked][:ip_3]..params[:blocked][:ip2_3]).each do |c|
             (params[:blocked][:ip_4]..params[:blocked][:ip2_4]).each do |d|
               @ip.push(a.to_s + "." + b.to_s + "." + c.to_s + "." + d.to_s)
             end
          end
       end
    end

    @ip.each do |ip|
       (params[:blocked][:port]..params[:blocked][:port2]).each do |port|
         @blocked = Blocked.new( :ip => ip, :port => port, :user_id => current_user.id )
         @blocked.protocols << Protocol.new( :name => $protocol_names[params[:blocked][:protocols].upcase])
       end
    end

    respond_to do |format|
      if @blocked.save
        format.html { redirect_to :action => 'ip'  }
      else
        format.html { redirect_to :action => 'index' }
      end
    end
  end
 
  # GET /dashboard/protocols
  def protocols
    @page_title = "Protocol Configuration"
    @nav_proto = "current"
    @blocked_protos = Solo_Protocol.find(:all).map { |proto| $protocol_ids[proto.protocol] }
    @allowed_protos = $protocol_names.keys - @blocked_protos
    @blocked_protos << "" 
    @allowed_protos << ""
 
    respond_to do |format|
      format.html
    end
  end
 
  def move_item
    protocol = params[:protocol].split("_")[0]
    list = params[:protocol].split("_")[1]
 
    if list=="blocked"
      Solo_Protocol.new({:protocol => $protocol_names[protocol]}).save!
    else
      Solo_Protocol.find(:all, :conditions => {:protocol => $protocol_names[protocol]}).each {|entry| entry.destroy}
    end
 
    render :update do |page|
      page.remove "protocol_#{protocol}"
      page.insert_html :top, list, render(:partial=>"protocol", :object => protocol)
      page.visual_effect :highlight, "protocol_#{protocol}"
    end
 
  end
 
  def force_update
    msg = Message.new
    msg.msg = "y helo thar"
 
    client = DaemonClient.new
    client.send(msg)
 
    flash[:notice] = "Update Sent!"
    redirect_to :action => "index"
  end

  def logout

  end 
 
 
  def auto_complete_for_blocked_protocols
    re = Regexp.new("#{params[:blocked][:protocols]}", "i")
    @protos = $protocol_names.keys.reject { |curr| !curr.match re }
    render :inline => "<%= content_tag(:ul, @protos.map { |org| content_tag(:li, h(org)) }) %>"
  end
 
  def chart_scale
    session[:interval] = params[:interval]
    session[:num] = params[:num]
    index
  end

  def reports
    @page_title = "Generate Custom Reports"
    @nav_report = "current"
  end

  def gen_report
    respond_to do |format|
      format.csv { send_data "1,2,3", :filename => Time.now.to_s + "_report.csv" }
    end
  end
  
  def init_chart
    title = Title.new("Firewall Traffic Overview")
    data1 = []

    session[:num] ||= 7
    session[:interval] ||= "Minutes"
    session[:avg] ||= 11
    session[:peak] ||= 15

    session[:num].to_i.times do |x|
      data1 << rand(5) + 1
    end

    line_traffic = Line.new
    line_traffic.text = "Incoming Traffic"
    line_traffic.width = 2
    line_traffic.colour = '#000000'
    line_traffic.values = data1

    line_peak = Line.new
    line_peak.text = "Peak Allowable Traffic"
    line_peak.width = 1
    line_peak.colour = '#FF0000'
    line_peak.values = [session[:peak].to_i] * session[:num].to_i

    line_avg = Line.new
    line_avg.text = "Average Allowable Traffic"
    line_avg.width = 1
    line_avg.colour = '#0000FF'
    line_avg.values = [session[:avg].to_i] * session[:num].to_i

    y = YAxis.new
    y.set_range(0,20,5)

    x_legend = XLegend.new(session[:interval])
    x_legend.set_style('{font-size: 10px; color: #000000}')

    y_legend = YLegend.new("kbps")
    y_legend.set_style('{font-size: 10px; color: #000000}')

    chart =OpenFlashChart.new
    chart.set_title(title)
    chart.set_x_legend(x_legend)
    chart.set_y_legend(y_legend)
    chart.y_axis = y

    chart.add_element(line_traffic)
    chart.add_element(line_peak)
    chart.add_element(line_avg)

    render :text => chart.to_s
  end
 
end
